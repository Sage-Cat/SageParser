#pragma once
#include <filesystem>
#include "IReader.hpp"
#include <unordered_set>
<<<<<<< HEAD
#include "pugixml.hpp"
=======
>>>>>>> f5c8d94cf7b49f9de629cccceb11a561298ec9e0
namespace SageDocs
{
    class XmlReader : public IReader
    {
    public:
        void setFilePath(const std::filesystem::path &new_path) override;
        std::shared_ptr<Dataset> readData() override;
        bool checkXMLStructure(const pugi::xml_node &node, std::unordered_set<int> &structureSet, int level = 0);

    protected:
        std::filesystem::path m_filePath{};
        std::unordered_set<int> structureSet;
    };
}
