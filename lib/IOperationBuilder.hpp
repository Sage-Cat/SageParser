#pragma once

#include <memory>
#include <vector>

#include "Readers/IReader.hpp"
#include "Writers/IWriter.hpp"
#include "Processors/IProcessor.hpp"

namespace SageParser
{
    class IOperationBuilder
    {
    public:
        IOperationBuilder() = default;
        virtual ~IOperationBuilder() = default;

        virtual void setReader(std::unique_ptr<IReader> reader) = 0;
        virtual void setProcessors(std::vector<std::unique_ptr<IProcessor>> processors) = 0;
        virtual void setWriter(std::unique_ptr<IWriter> writer) = 0;
        virtual void performOperation() = 0;
    };

}
