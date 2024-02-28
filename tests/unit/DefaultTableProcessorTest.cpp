#include <gtest/gtest.h>
#include <memory>
#include <algorithm>

#include "Table.hpp"
#include "Processors/DefaultTableProcessor.hpp"

namespace SageParserTest
{
    using namespace SageParser;

    class DefaultTableProcessorTest : public ::testing::Test
    {
    protected:
        std::shared_ptr<Table> inputTable;
        std::shared_ptr<DefaultTableProcessor> processor;

        void SetUp() override
        {
            inputTable = std::make_shared<Table>();
            (*inputTable)["NAME"] = {"Alice", "Bob"};
            (*inputTable)["Count"] = {"10", "20"};
            (*inputTable)["UNIT"] = {"шт", "бочк"};
            (*inputTable)["price"] = {"100", "200"};
            (*inputTable)["IrrelevantColumn"] = {"irrelevant1", "irrelevant2"};

            processor = std::make_shared<DefaultTableProcessor>();
        }
    };

    TEST_F(DefaultTableProcessorTest, RemoveUnrecognizedColumn)
    {
        auto processedTable = processor->process(inputTable);
        auto columnNames = processedTable->columnNames();

        // IrrelevantColumn had to be removed
        auto found = std::ranges::find(columnNames, "IrrelevantColumn") != columnNames.end();
        EXPECT_FALSE(found) << "Irrelevant columns should be removed.";
    }

    TEST_F(DefaultTableProcessorTest, RenameColumnsToDefault)
    {
        auto processedTable = processor->process(inputTable);

        std::vector<std::string> expectedNames = {"name", "count", "unit", "price"};
        auto columnNames = processedTable->columnNames();

        for (const auto &expectedName : expectedNames)
        {
            auto found = std::ranges::find(columnNames, expectedName) != columnNames.end();
            EXPECT_TRUE(found) << "Expected column " << expectedName << " not found.";
        }
    }

    TEST_F(DefaultTableProcessorTest, RenameUnitsToDefault)
    {
        auto processedTable = processor->process(inputTable);

        const auto &unitColumn = (*processedTable)["unit"];
        EXPECT_EQ(unitColumn[0], "шт.") << "Unit value should be standardized to 'шт.'";
        EXPECT_EQ(unitColumn[1], "Бочка") << "Unit value should be standardized to 'Бочка'";
    }

} // namespace SageParserTest
