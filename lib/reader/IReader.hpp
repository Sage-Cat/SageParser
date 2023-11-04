#pragma once

#include "Dataset.hpp"

namespace SageDocs
{
    enum class ReaderReaderFileType : int
    {
        // uncomment when ready
        CSV = 0,
        XLSX
    };

    class IReader
    {
    public:
        virtual RawData readData() = 0;
    };
}