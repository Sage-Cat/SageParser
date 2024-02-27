#pragma once

#include "IWriter.hpp"

namespace SageParser
{
    class CsvWriter : public IWriter
    {
    public:
        CsvWriter() = default;

        void setFilePath(const std::filesystem::path &new_path) override;

        void writeData(const std::shared_ptr<Table> &Table) override;

    private:
        std::filesystem::path m_filePath;
    };
}