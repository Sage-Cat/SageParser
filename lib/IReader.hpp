#pragma once

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
        virtual void setFileName(const std::string &name) = 0;
        virtual std::shared_ptr<Dataset> readData() = 0;
    };
}