#include "XmlWriter.hpp"
#include "pugixml.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <queue>

namespace SageDocs
{
    void XmlWriter::setFilePath(const std::filesystem::path &new_path)
    {
        if (!std::filesystem::exists(new_path.parent_path()))
            throw std::invalid_argument("Directory path - " + new_path.string() + " does not exist.");

        if (std::filesystem::is_directory(new_path))
            throw std::invalid_argument("File path - " + new_path.string() + " is a directory.");

        m_filePath = new_path;
    }
    void XmlWriter::writeData(const std::shared_ptr<Dataset> &dataset)
    {
        // queue for columnNames
        std::queue<std::string> q;
        pugi::xml_document doc;
        pugi::xml_node declaration = doc.prepend_child(pugi::node_declaration);
        declaration.append_attribute("version") = "1.0";
        declaration.append_attribute("encoding") = "WINDOWS-1251";

        pugi::xml_node root = doc.append_child("Root");
        for (auto columnName : dataset->columnNames)
        {
            q.push(columnName);
        }

        for (auto data : dataset->dataRows)
        {
            pugi::xml_node price = root.append_child("Price");
            for (auto node_text : data)
            {
                if (!q.empty())
                {
                    auto node_name = q.front();
                    q.pop();
                    pugi::xml_node child1 = price.append_child(node_name.c_str());
                    const char *text = node_text.c_str();
                    child1.text().set(text);
                }
                else
                    throw std::runtime_error("queue is empty");
            }
        }
        doc.save_file("result.xml");
    }

}