#pragma once

#include "ITableProcessor.hpp"

namespace SageParser
{
    class DataProcessorFactory
    {
    public:
        DataProcessorFactory() = delete;
        ~DataProcessorFactory() = delete;

        static std::unique_ptr<ITableProcessor> createDataProcessor(DocType type);
    };
}