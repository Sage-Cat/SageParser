#include "XmlWriter.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include "pugixml.hpp"

namespace SageParser
{
    void XmlWriter::write(const std::shared_ptr<Table> &table)
    {
        // Pre-checks to validate the file path
        auto parentPath = filePath_.parent_path();
        if (!std::filesystem::exists(parentPath))
        {
            throw std::invalid_argument("Directory path - " + parentPath.string() + " does not exist.");
        }

        if (std::filesystem::is_directory(filePath_))
        {
            throw std::invalid_argument("File path - " + filePath_.string() + " is a directory, not a file.");
        }

        // Initialize XML document
        pugi::xml_document doc;
        auto declaration = doc.prepend_child(pugi::node_declaration);
        declaration.append_attribute("version") = "1.0";
        declaration.append_attribute("encoding") = "UTF-8";

        auto root = doc.append_child("Root");

        // Fetch column names and row count from the table
        const auto columnNamesMap = table->columnNamesMap();
        const auto numRows = table->rowCount();
        const auto numColumns = table->columnCount();

        // Construct XML document
        for (size_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
        {
            auto rowNode = root.append_child("Row");
            for (size_t columnIndex = 0; columnIndex < numColumns; ++columnIndex)
            {
                std::string columnName = columnNamesMap.at(columnIndex); // Use .at() for safe access
                std::string cellValue = table->at(rowIndex, columnIndex);

                auto cellNode = rowNode.append_child(columnName.c_str());
                cellNode.text().set(cellValue.c_str());
            }
        }

        // Save XML document to file
        if (!doc.save_file(filePath_.c_str()))
        {
            std::cerr << "Failed to save XML file to " << filePath_ << std::endl;
        }
        else
        {
            std::cout << "XML file was saved successfully to " << filePath_ << std::endl;
        }
    }
}