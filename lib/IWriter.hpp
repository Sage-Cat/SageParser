#pragma once

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
        virtual void writeData(const Dataset &dataset) = 0;
    };
}