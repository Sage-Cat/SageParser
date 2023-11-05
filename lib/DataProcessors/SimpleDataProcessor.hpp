#pragma once

#include "IDataProcessor.hpp"

namespace SageDocs
{
    class SimpleDataProcessor : public IDataProcessor
    {
        Dataset parse(const RawData data) override;
    };
}