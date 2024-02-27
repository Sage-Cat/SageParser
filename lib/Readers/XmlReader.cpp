#include <filesystem>
#include <stdexcept>
#include <iostream>
#include "XmlReader.hpp"

namespace SageParser
{
    void XmlReader::setFilePath(const std::filesystem::path &new_path)
    {
        if (!std::filesystem::exists(new_path))
            throw std::invalid_argument("File path- " + new_path.string() + " does not exist.");

        if (!std::filesystem::is_regular_file(new_path))
            throw std::invalid_argument("File path - " + new_path.string() + " pointing not to a file.");

        m_filePath = new_path;
    }

    // checking the xml file for tabularity
    bool XmlReader::checkXMLStructure(const pugi::xml_node &node, std::unordered_set<int> &structureSet, int level)
    {
        int childrenCount = std::distance(node.begin(), node.end());
        structureSet.insert(childrenCount);
        for (pugi::xml_node childNode : node.children())
        {
            if (!checkXMLStructure(childNode, structureSet, level + 1))
            {
                return false;
            }
        }
        return true;
    }

    std::shared_ptr<Table> XmlReader::readData()
    {
        int level = 0;
        auto Table = std::make_shared<Table>();
        pugi::xml_document doc;
        if (!doc.load_file(m_filePath.c_str()))
        {
            std::cout << "Error loading XML file." << std::endl
                      << std::endl;
        }
        if (!checkXMLStructure(doc, m_structureSet, level))
        {
            std::cout << "Invalid XML structure: Expected tabular data." << std::endl
                      << std::endl;
        }
        pugi::xml_node items = doc.first_child();
        try
        {
            auto item = doc.first_child();
            for (item; item != PUGIXML_NULL; item = item.first_child())
            {
                if (!item.first_child().first_child())
                {
                    item = item.parent();
                    break;
                }
            }
            for (item; item != PUGIXML_NULL; item = item.next_sibling())
            {
                std::vector<std::string> tmp;
                for (pugi::xml_node columnNode : item.children())
                {
                    Table->columnNames.emplace_back(columnNode.name());
                    tmp.push_back(columnNode.text().as_string());
                }
                Table->dataRows.emplace_back(tmp);
            }
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
            // Additional steps to handle the error, such as terminating the program or requesting another file.
        }
        return Table;
    }
}