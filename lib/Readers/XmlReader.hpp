#pragma once
#include <filesystem>
#include "IReader.hpp"

namespace SageDocs
{
    class XmlReader : public IReader
    {
    public:
        void setFilePath(const std::filesystem::path &new_path) override;
        std::shared_ptr<Dataset> readData() override;

    protected:
        std::filesystem::path m_filePath{};
    };
}
