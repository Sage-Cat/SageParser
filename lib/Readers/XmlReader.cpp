#include "XmlReader.hpp"

#include <filesystem>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

#include "pugixml.hpp"

namespace SageParser
{
    std::shared_ptr<Table> XmlReader::read()
    {
        if (filePath_.empty())
            throw std::runtime_error("File path is empty");
        if (!std::filesystem::exists(filePath_)
            || !std::filesystem::is_regular_file(filePath_))
            throw std::runtime_error("Invalid XML file path: " + filePath_.string());

        pugi::xml_document document;
        const pugi::xml_parse_result result = document.load_file(filePath_.c_str());
        if (!result)
            throw std::runtime_error("Failed to parse XML file " + filePath_.string()
                                     + ": " + result.description());

        const pugi::xml_node root = document.document_element();
        if (!root)
            throw std::runtime_error("XML document has no root element");

        std::vector<pugi::xml_node> rows;
        std::vector<std::string> columns;
        std::unordered_set<std::string> knownColumns;

        for (const pugi::xml_node row : root.children())
        {
            if (row.type() != pugi::node_element)
                continue;
            rows.push_back(row);
            for (const pugi::xml_node cell : row.children())
            {
                if (cell.type() != pugi::node_element)
                    continue;
                const std::string name = cell.name();
                if (knownColumns.insert(name).second)
                    columns.push_back(name);
            }
        }

        if (rows.empty() || columns.empty())
            throw std::runtime_error("XML document contains no tabular data");

        auto table = std::make_shared<Table>();
        for (const std::string &column : columns)
            table->addColumn(column);

        for (const pugi::xml_node row : rows)
        {
            std::map<std::string, std::string> rowData;
            for (const pugi::xml_node cell : row.children())
            {
                if (cell.type() != pugi::node_element)
                    continue;
                const std::string name = cell.name();
                if (!rowData.emplace(name, cell.text().as_string()).second)
                    throw std::runtime_error("Duplicate XML field in one row: " + name);
            }
            table->addRow(rowData);
        }

        return table;
    }
} // namespace SageParser
