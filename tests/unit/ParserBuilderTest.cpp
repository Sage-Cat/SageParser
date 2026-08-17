#include <gtest/gtest.h>

#include <filesystem>
#include <memory>
#include <vector>

#include "ParserBuilder.hpp"

namespace SageParserTest
{
    using namespace SageParser;

    class StubReader final : public IReader
    {
    public:
        explicit StubReader(bool returnNull = false)
            : IReader(std::filesystem::path {}), returnNull_(returnNull) {}

        std::shared_ptr<Table> read() override
        {
            return returnNull_ ? nullptr : std::make_shared<Table>();
        }

    private:
        bool returnNull_;
    };

    class StubWriter final : public IWriter
    {
    public:
        StubWriter() : IWriter(std::filesystem::path {}) {}
        void write(const std::shared_ptr<Table> &) override {}
    };

    TEST(ParserBuilderTest, RequiresReaderAndWriter)
    {
        ParserBuilder builder;
        EXPECT_THROW(builder.performOperation(), std::runtime_error);

        builder.setReader(std::make_unique<StubReader>());
        EXPECT_THROW(builder.performOperation(), std::runtime_error);
    }

    TEST(ParserBuilderTest, RejectsNullPipelineResults)
    {
        ParserBuilder nullReaderResult;
        nullReaderResult.setReader(std::make_unique<StubReader>(true));
        nullReaderResult.setWriter(std::make_unique<StubWriter>());
        EXPECT_THROW(nullReaderResult.performOperation(), std::runtime_error);

        ParserBuilder nullProcessor;
        nullProcessor.setReader(std::make_unique<StubReader>());
        nullProcessor.setWriter(std::make_unique<StubWriter>());
        std::vector<std::unique_ptr<IProcessor>> processors;
        processors.push_back(nullptr);
        nullProcessor.setProcessors(std::move(processors));
        EXPECT_THROW(nullProcessor.performOperation(), std::runtime_error);
    }
} // namespace SageParserTest
