#pragma once

#include <filesystem>

#include "Table.hpp"
#include "Types.hpp"

namespace SageParser
{
    class IReader
    {
    public:
        virtual void setFilePath(const std::filesystem::path &new_path) = 0;
        virtual void setDelimiter(char new_delimiter) = 0;
        virtual std::shared_ptr<Table> readData() = 0;
    };
}