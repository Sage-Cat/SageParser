#include <filesystem>
#include <stdexcept>
#include <iostream>
#include "XmlReader.hpp"
#include "pugixml.hpp"
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
        pugi::xml_document doc;
        std::filesystem::path filePath = m_filePath;
        if (!checkXMLStructure(doc, structureSet))
        {
            throw std::runtime_error("Invalid XML structure: Expected tabular data.");
        }
        std::string filePathStr = filePath.string();
        pugi::xml_parse_result result = doc.load_file(filePathStr.c_str());
        if (!result)
        {
            throw result.description();
        }
        // pugi::xml_node items = doc.child("Root");
        pugi::xml_node items = doc.first_child();
        auto dataset = std::make_shared<Dataset>();
        for (auto parent = items; parent != PUGIXML_NULL; parent = parent.next_sibling())
        {
            while (parent.first_child())
            {
                parent = parent.first_child();
            }
            parent = parent.parent();
            parent = parent.parent();
            parent = parent.parent();
            for (auto c = parent.first_child(); c != PUGIXML_NULL; c = c.next_sibling())
            {
                std::string childName = c.name();
                std::vector<std::string> tmp;

                for (auto i = c.first_child(); i != PUGIXML_NULL; i = i.next_sibling())
                {
                    dataset->columnNames.push_back(i.name());
                    tmp.push_back(i.text().as_string());
                }
                dataset->dataRows.push_back(tmp);
            }
        }
        return dataset;
    }
}
