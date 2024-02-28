#pragma once

#include <filesystem>
#include <memory>
#include <vector>
#include <ranges>

#include "IOperationBuilder.hpp"

#include "Readers/IReader.hpp"
#include "Writers/IWriter.hpp"
#include "Processors/IProcessor.hpp"

namespace SageParser
{
    class ParserBuilder : public IOperationBuilder
    {
    public:
        ParserBuilder() = default;
        ~ParserBuilder() override = default;

        void setReader(std::unique_ptr<IReader> reader) override;
        void setProcessors(std::vector<std::unique_ptr<IProcessor>> processors) override;
        void setWriter(std::unique_ptr<IWriter> writer) override;
        void performOperation() override;

    private:
        std::unique_ptr<IReader> reader_;
        std::vector<std::unique_ptr<IProcessor>> processors_;
        std::unique_ptr<IWriter> writer_;
    };
}
