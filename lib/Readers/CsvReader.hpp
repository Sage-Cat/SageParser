#pragma once

#include <filesystem>
#include <memory>

#include "IReader.hpp"
#include "DataTable.hpp"

namespace SageParser
{
    class CsvReader : public IReader
    {
    public:
        CsvReader(const std::filesystem::path &filePath, char delimiter = ',')
            : IReader(filePath), m_delimiter(delimiter) {}

        std::shared_ptr<DataTable> read() override;

    private:
        char m_delimiter;
    };
}
