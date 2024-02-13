#pragma once
#include <filesystem>
#include "IReader.hpp"
#include <unordered_set>
#include "pugixml.hpp"

namespace SageDocs
{
    class XmlReader : public IReader
    {
    public:
        XmlReader() = default;
        void setDelimiter(char new_delimiter) override {}
        void setFilePath(const std::filesystem::path &new_path) override;
        std::shared_ptr<Dataset> readData() override;
        bool checkXMLStructure(const pugi::xml_node &node, std::unordered_set<int> &structureSet, int level);

    protected:
        std::filesystem::path m_filePath{};
        std::unordered_set<int> m_structureSet;
    };
}