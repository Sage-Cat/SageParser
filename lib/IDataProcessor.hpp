#pragma once

#include "Dataset.hpp"
#include "Types.hpp"

namespace SageDocs
{
    class IDataProcessor
    {
    public:
        virtual std::shared_ptr<Dataset> process(const std::shared_ptr<Dataset> &dataset) = 0;
    };
}