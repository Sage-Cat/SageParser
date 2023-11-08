#pragma once

#include <memory>
#include <filesystem>

#include "Dataset.hpp"

namespace SageDocs
{
    enum class ReaderFileType : int
    {
        CSV = 0,
        XLSX
    };

    class IReader
    {
    public:
        virtual void setFilePath(const std::filesystem::path &new_path) = 0;
        virtual std::shared_ptr<Dataset> readData() = 0;
    };
}