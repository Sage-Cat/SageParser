#pragma once

#include "IWriter.hpp"

namespace SageDocs
{
    class CsvWriter : public IWriter
    {
    public:
        CsvWriter() = default;

        void setFilePath(const std::filesystem::path &new_path) override;

        void writeData(const std::shared_ptr<Dataset> &dataset) override;

    protected:
        std::filesystem::path m_filePath;
    };
}