#include "XmlWriter.hpp"

#include <cctype>
#include <filesystem>
#include <stdexcept>
#include <string_view>

#include "pugixml.hpp"

namespace SageParser
{
    namespace
    {
        bool isXmlElementName(std::string_view name)
        {
            if (name.empty())
                return false;
            const auto first = static_cast<unsigned char>(name.front());
            if (!(std::isalpha(first) || first == '_'))
                return false;

            for (const unsigned char character : name.substr(1))
            {
                if (!(std::isalnum(character) || character == '_'
                      || character == '-' || character == '.'))
                    return false;
            }
            return true;
        }
    }

    void XmlWriter::write(const std::shared_ptr<Table> &table)
    {
        if (!table)
            throw std::invalid_argument("Table must not be null");
        if (filePath_.empty())
            throw std::invalid_argument("File path is empty");
        if (table->columnCount() == 0)
            throw std::invalid_argument("XML output requires at least one column");
        if (table->rowCount() == 0)
            throw std::invalid_argument("XML output requires at least one table row");

        const std::filesystem::path parent = filePath_.parent_path();
        if (!parent.empty() && (!std::filesystem::exists(parent)
                                || !std::filesystem::is_directory(parent)))
            throw std::invalid_argument("Output directory does not exist: " + parent.string());
        if (std::filesystem::is_directory(filePath_))
            throw std::invalid_argument("Output path is a directory: " + filePath_.string());

        const auto columnNames = table->columnNamesMap();
        for (const auto &[index, name] : columnNames)
        {
            (void)index;
            if (!isXmlElementName(name))
                throw std::invalid_argument("Column is not a supported XML element name: " + name);
        }

        pugi::xml_document document;
        auto declaration = document.prepend_child(pugi::node_declaration);
        declaration.append_attribute("version") = "1.0";
        declaration.append_attribute("encoding") = "UTF-8";
        auto root = document.append_child("Root");

        for (std::size_t row = 0; row < table->rowCount(); ++row)
        {
            auto rowNode = root.append_child("Row");
            for (std::size_t column = 0; column < table->columnCount(); ++column)
            {
                const std::string &name = columnNames.at(static_cast<int>(column));
                auto cell = rowNode.append_child(name.c_str());
                cell.text().set(table->at(static_cast<int>(row),
                                          static_cast<int>(column)).c_str());
            }
        }

        if (!document.save_file(filePath_.c_str()))
            throw std::runtime_error("Failed to write XML file: " + filePath_.string());
    }
} // namespace SageParser
