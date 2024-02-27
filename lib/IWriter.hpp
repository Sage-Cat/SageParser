#pragma once

#include <filesystem>

#include "Table.hpp"
#include "Types.hpp"

namespace SageParser
{
    class IWriter
    {
    public:
        virtual void setFilePath(const std::filesystem::path &new_path) = 0;
        virtual void writeData(const std::shared_ptr<Table> &Table) = 0;
    };
}