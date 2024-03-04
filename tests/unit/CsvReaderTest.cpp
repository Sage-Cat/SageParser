#include <gtest/gtest.h>

#include <fstream>
#include <filesystem>

#include "Readers/CsvReader.hpp"

namespace SageParserTest
{
    using namespace SageParser;

    class CsvReaderTest : public ::testing::Test
    {
    protected:
        std::filesystem::path tempFilePath;
        char delimiter = ',';

        void SetUp() override
        {
            tempFilePath = std::filesystem::temp_directory_path() / "test.csv";

            // Setup a minimal CSV content
            std::ofstream ofs(tempFilePath);
            ofs << "ID,Name\n1,John Doe\n2,Jane Doe";
            ofs.close();
        }

        void TearDown() override
        {
            std::filesystem::remove(tempFilePath);
        }
    };

    TEST_F(CsvReaderTest, ReadTableFromFile)
    {
        CsvReader reader(tempFilePath, delimiter);
        auto table = reader.read();

        // Check that the table is not null
        ASSERT_NE(table, nullptr);

        // Check the number of columns and rows is correct
        EXPECT_EQ(table->columnCount(), 2) << "Table should have exactly 2 columns.";
        EXPECT_EQ(table->rowCount(), 2) << "Table should have exactly 2 rows.";

        // Check that the column names are correct
        auto columnNamesMap = table->columnNamesMap();
        std::vector<std::string> columnNames;
        for (const auto &[index, name] : columnNamesMap)
        {
            columnNames.push_back(name);
        }
        EXPECT_NE(std::find(columnNames.begin(), columnNames.end(), "ID"), columnNames.end()) << "Column 'ID' not found.";
        EXPECT_NE(std::find(columnNames.begin(), columnNames.end(), "Name"), columnNames.end()) << "Column 'Name' not found.";

        // Check the content of the table
        EXPECT_EQ(table->at(0, "ID"), "1") << "First entry of 'ID' column should be '1'.";
        EXPECT_EQ(table->at(1, "ID"), "2") << "Second entry of 'ID' column should be '2'.";
        EXPECT_EQ(table->at(0, "Name"), "John Doe") << "First entry of 'Name' column should be 'John Doe'.";
        EXPECT_EQ(table->at(1, "Name"), "Jane Doe") << "Second entry of 'Name' column should be 'Jane Doe'.";
    }

    TEST_F(CsvReaderTest, ThrowWhenFileNotFound)
    {
        std::filesystem::path invalidPath = "nonexistent.csv";
        CsvReader reader(invalidPath, delimiter);

        EXPECT_THROW(
            {
                reader.read();
            },
            std::invalid_argument);
    }

} // namespace SageParserTest
