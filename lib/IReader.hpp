#pragma once

#include <filesystem>

#include "Dataset.hpp"
#include "Types.hpp"

namespace SageDocs
{
<<<<<<< HEAD
=======
    enum class ReaderFileType : int
    {
        CSV = 0,
        XLSX,
        XML
    };

>>>>>>> f5c8d94cf7b49f9de629cccceb11a561298ec9e0
    class IReader
    {
    public:
        virtual void setFilePath(const std::filesystem::path &new_path) = 0;
        virtual void setDelimiter(char new_delimiter) = 0;
        virtual std::shared_ptr<Dataset> readData() = 0;
    };
}