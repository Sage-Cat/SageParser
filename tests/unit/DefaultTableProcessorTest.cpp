#include <gtest/gtest.h>

#include <memory>
#include <algorithm>

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

            // Add columns
            inputTable->addColumn("NAME");
            inputTable->addColumn("Count");
            inputTable->addColumn("UNIT");
            inputTable->addColumn("price");
            inputTable->addColumn("IrrelevantColumn");

            // Add rows
            inputTable->addRow({{"NAME", "Alice"}, {"Count", "10"}, {"UNIT", "шт"}, {"price", "100"}, {"IrrelevantColumn", "irrelevant1"}});
            inputTable->addRow({{"NAME", "Bob"}, {"Count", "20"}, {"UNIT", "бочк"}, {"price", "200"}, {"IrrelevantColumn", "irrelevant2"}});

            processor = std::make_shared<DefaultTableProcessor>();
        }
    };

    TEST_F(DefaultTableProcessorTest, RemoveUnrecognizedColumn)
    {
        auto processedTable = processor->process(inputTable);
        auto columnNamesMap = processedTable->columnNamesMap();

        // Convert columnNames map to vector of string for easier searching
        std::vector<std::string> columnNames;
        for (const auto &[index, name] : columnNamesMap)
        {
            columnNames.push_back(name);
        }

        // Check for IrrelevantColumn
        auto found = std::find(columnNames.begin(), columnNames.end(), "IrrelevantColumn") != columnNames.end();
        EXPECT_FALSE(found) << "Irrelevant columns should be removed.";
    }

    TEST_F(DefaultTableProcessorTest, RenameColumnsToDefault)
    {
        auto processedTable = processor->process(inputTable);

        // Convert columnNames map to vector of string for easier searching
        std::vector<std::string> columnNames;
        auto columnNamesMap = processedTable->columnNamesMap();
        for (const auto &[index, name] : columnNamesMap)
        {
            columnNames.push_back(name);
        }

        std::vector<std::string> expectedNames{
            Default::ColumnNames::NAME.data(),
            Default::ColumnNames::COUNT.data(),
            Default::ColumnNames::UNIT.data(),
            Default::ColumnNames::PRICE.data()};
        for (const auto &expectedName : expectedNames)
        {
            auto found = std::find(columnNames.begin(), columnNames.end(), expectedName) != columnNames.end();
            EXPECT_TRUE(found) << "Expected column " << expectedName << " not found.";
        }
    }

    TEST_F(DefaultTableProcessorTest, RenameUnitsToDefault)
    {
        auto processedTable = processor->process(inputTable);

        EXPECT_EQ(
            processedTable->at(0, Default::ColumnNames::UNIT.data()),
            Default::Units::PIECE)
            << "Unit value should be standardized to 'шт.'";
        EXPECT_EQ(
            processedTable->at(1, Default::ColumnNames::UNIT.data()),
            Default::Units::BARREL)
            << "Unit value should be standardized to 'Бочка'";
    }

} // namespace SageParserTest
