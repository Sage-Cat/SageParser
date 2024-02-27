#pragma once

#include <filesystem>
#include <memory>

#include "IWriter.hpp"
#include "DataTable.hpp"

namespace SageParser
{
    class CsvWriter : public IWriter
    {
    public:
        explicit CsvWriter(const std::filesystem::path &new_path) : IWriter(new_path) {}

        void write(const std::shared_ptr<DataTable> &dataTable) override;
    };
}
