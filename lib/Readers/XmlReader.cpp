#include <filesystem>
#include <stdexcept>
#include <iostream>
#include "XmlReader.hpp"

namespace SageParser
{

    std::shared_ptr<Table> XmlReader::read()
    {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(filePath_.c_str());

        if (!result)
        {
            std::cerr << "Error loading XML file: " << filePath_ << " - " << result.description() << std::endl;
            throw std::runtime_error("Failed to load XML file.");
        }

        auto table = std::make_shared<Table>();
        pugi::xml_node root = doc.document_element(); // Using document_element for clarity

        // Using structured bindings (C++17 feature also useful in C++20 contexts)
        bool columnsInitialized = false;
        for (auto &rowNode : root.children())
        {
            if (!columnsInitialized)
            {
                for (auto &columnNode : rowNode.children())
                {
                    table->addColumn(columnNode.name());
                }
                columnsInitialized = true;
            }

            std::map<std::string, std::string> rowData;
            for (auto &columnNode : rowNode.children())
            {
                rowData[columnNode.name()] = columnNode.text().as_string();
            }
            table->addRow(rowData);
        }

        if (!columnsInitialized)
        {
            std::cerr << "No data found in XML." << std::endl;
            throw std::runtime_error("Empty XML structure.");
        }

        return table;
    }

} // namespace SageParser