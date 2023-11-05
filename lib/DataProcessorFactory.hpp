#pragma once

#include <memory>

#include "IDataProcessor.hpp"

namespace SageDocs
{
    class DataProcessorFactory
    {
    public:
        DataProcessorFactory() = delete;
        ~DataProcessorFactory() = delete;

        static std::unique_ptr<IDataProcessor> createDataProcessor(DocType type);
    };
}