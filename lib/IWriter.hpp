#pragma once

#include <memory>
#include <filesystem>

#include "Dataset.hpp"

namespace SageDocs
{
    enum class WriterFileType : int
    {
        CSV = 0,
        XML
    };

    class IWriter
    {
    public:
        virtual void setFilePath(const std::filesystem::path &new_path) = 0;
        virtual void writeData(const std::shared_ptr<Dataset> &dataset) = 0;
    };
}