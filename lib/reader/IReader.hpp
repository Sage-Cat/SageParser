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
        virtual RawData readData() = 0;
    };
}