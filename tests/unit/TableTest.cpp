#include <gtest/gtest.h>

#include "Table.hpp"

namespace SageParserTest
{
    using SageParser::Table;

    TEST(TableTest, RejectsInvalidIndexesAndNames)
    {
        Table table;
        table.addColumn("first");
        table.addRow({{"first", "value"}});

        EXPECT_THROW(table.at(-1, 0), std::out_of_range);
        EXPECT_THROW(table.at(0, -1), std::out_of_range);
        EXPECT_THROW(table.at(0, "missing"), std::out_of_range);
        EXPECT_THROW(table.addRow({{"missing", "value"}}), std::out_of_range);
        EXPECT_THROW(table.addColumn(""), std::invalid_argument);
        EXPECT_THROW(table.addColumn("first"), std::invalid_argument);
    }

    TEST(TableTest, PreservesDataWhenColumnsChange)
    {
        Table table;
        table.addColumn("first");
        table.addColumn("middle");
        table.addColumn("last");
        table.addRow({{"first", "A"}, {"middle", "B"}, {"last", "C"}});

        table.eraseColumn(1);
        ASSERT_EQ(table.columnCount(), 2);
        EXPECT_EQ(table.columnNamesMap().at(0), "first");
        EXPECT_EQ(table.columnNamesMap().at(1), "last");
        EXPECT_EQ(table.at(0, 0), "A");
        EXPECT_EQ(table.at(0, 1), "C");

        table.renameColumn(1, "renamed");
        EXPECT_EQ(table.at(0, "renamed"), "C");
        EXPECT_THROW(table.renameColumn(1, "first"), std::invalid_argument);
    }

    TEST(TableTest, ReserveDoesNotCreateLogicalRows)
    {
        Table table;
        table.reserve(100, 10);
        EXPECT_EQ(table.rowCount(), 0);
        EXPECT_EQ(table.columnCount(), 0);
    }
} // namespace SageParserTest
