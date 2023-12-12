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
    std::shared_ptr<Dataset> XmlReader::readData()
    {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(m_filePath);
        // std::wcout.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t, 0x10FFFF, std::generate_header>()));
        if (!result)
        {
            throw result.description();
        }
        pugi::xml_node items = doc.child("Root");
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
            return dataset;
        }
    }
}
