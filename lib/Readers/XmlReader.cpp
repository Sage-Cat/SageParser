#include <filesystem>
#include <stdexcept>
#include <iostream>
#include "XmlReader.hpp"
<<<<<<< HEAD

=======
#include "pugixml.hpp"
>>>>>>> f5c8d94cf7b49f9de629cccceb11a561298ec9e0
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
<<<<<<< HEAD
    // checking the xml file for tabularity
=======
>>>>>>> f5c8d94cf7b49f9de629cccceb11a561298ec9e0
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
<<<<<<< HEAD
        auto dataset = std::make_shared<Dataset>();
        pugi::xml_document doc;
        std::string filePathAsString = m_filePath.string();
        const char *filePathAsCString = filePathAsString.c_str();
        if (!doc.load_file(filePathAsCString))
        {
            throw std::runtime_error("Error loading XML file.");
        }
=======
        pugi::xml_document doc;
        std::filesystem::path filePath = m_filePath;
>>>>>>> f5c8d94cf7b49f9de629cccceb11a561298ec9e0
        if (!checkXMLStructure(doc, structureSet))
        {
            throw std::runtime_error("Invalid XML structure: Expected tabular data.");
        }
<<<<<<< HEAD
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
=======
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
>>>>>>> f5c8d94cf7b49f9de629cccceb11a561298ec9e0
                }
                dataset->dataRows.push_back(tmp);
            }
        }
<<<<<<< HEAD
        catch (const std::runtime_error &e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
            // Additional steps to handle the error, such as terminating the program or requesting another file.
        }
=======
>>>>>>> f5c8d94cf7b49f9de629cccceb11a561298ec9e0
        return dataset;
    }
}
