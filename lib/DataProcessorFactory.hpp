#pragma once

#include "IDataProcessor.hpp"

namespace SageParser
{
    class DataProcessorFactory
    {
    public:
        DataProcessorFactory() = delete;
        ~DataProcessorFactory() = delete;

        static std::unique_ptr<IDataProcessor> createDataProcessor(DocType type);
    };
}