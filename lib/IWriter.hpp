#pragma once

#include <filesystem>

#include "Dataset.hpp"
#include "Types.hpp"

namespace SageDocs
{
    class IWriter
    {
    public:
        virtual void setFilePath(const std::filesystem::path &new_path) = 0;
        virtual void writeData(const std::shared_ptr<Dataset> &dataset) = 0;
    };
}