#pragma once

#include "Dataset.hpp"

namespace SageDocs
{
    enum class DocType : int
    {
        // uncomment when ready
        // SIMPLE_TABLE = 0,
        // BESUGLAYA_INVOICE
    };

    class IDataProcessor
    {
    public:
        virtual Dataset parse(const RawData data) = 0;
    };
}