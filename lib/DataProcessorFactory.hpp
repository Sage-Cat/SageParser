#pragma once

#include "IDataTableProcessor.hpp"

namespace SageParser
{
    class DataProcessorFactory
    {
    public:
        DataProcessorFactory() = delete;
        ~DataProcessorFactory() = delete;

        static std::unique_ptr<IDataTableProcessor> createDataProcessor(DocType type);
    };
}