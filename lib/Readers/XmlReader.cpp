#include <filesystem>
#include <stdexcept>
#include <iostream>
#include "XmlReader.hpp"

namespace SageDocs
{
    void XmlReader::setFilePath(const std::filesystem::path &new_path)
    {
        if (!std::filesystem::exists(new_path))
            throw std::invalid_argument("File path does not exist.");

        if (!std::filesystem::is_regular_file(new_path))
            throw std::invalid_argument("File path pointing not to a file.");

        m_filePath = new_path;
    }
    // checking the xml file for tabularity
    bool checkXMLStructure(const pugi::xml_node &node, std::unordered_set<int> &structureSet, int level = 0)
    {
        int childrenCount = 0;
        for (pugi::xml_node childNode : node.children())
        {
            childrenCount++;
        }
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
    std::shared_ptr<Dataset> XmlReader::readData()
    {
        auto dataset = std::make_shared<Dataset>();
        pugi::xml_document doc;
        std::string filePathAsString = m_filePath.string();
        const char *filePathAsCString = filePathAsString.c_str();
        if (!doc.load_file(filePathAsCString))
        {
            throw std::runtime_error("Error loading XML file.");
        }
        if (!checkXMLStructure(doc, structureSet))
        {
            throw std::runtime_error("Invalid XML structure: Expected tabular data.");
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
                    dataset->columnNames.push_back(columnNode.name());
                    tmp.push_back(columnNode.text().as_string());
                }
                dataset->dataRows.push_back(tmp);
            }
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
            // Additional steps to handle the error, such as terminating the program or requesting another file.
        }
        return dataset;
    }
}
