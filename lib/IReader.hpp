#pragma once

#include <filesystem>

#include "Dataset.hpp"
#include "Types.hpp"

namespace SageDocs
{
    class IReader
    {
    public:
        virtual void setFilePath(const std::filesystem::path &new_path) = 0;
        virtual void setDelimiter(char new_delimiter) = 0;
        virtual std::shared_ptr<Dataset> readData() = 0;
    };
}