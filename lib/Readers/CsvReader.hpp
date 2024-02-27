#pragma once

#include <filesystem>

#include "IReader.hpp"

namespace SageParser
{
    class CsvReader : public IReader
    {
    public:
        CsvReader() = default;

        // Interface methods
        void setFilePath(const std::filesystem::path &new_path) override;
        void setDelimiter(char new_delimiter) override;
        std::shared_ptr<Table> readData() override;

    private:
        std::filesystem::path m_filePath{};
        char m_delimiter{','};
    };
}
