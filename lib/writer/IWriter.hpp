#pragma once

#include "Dataset.hpp"

namespace SageDocs
{
    class IWriter
    {
    public:
        virtual void writeData(const Dataset &dataset) = 0;
    };
}