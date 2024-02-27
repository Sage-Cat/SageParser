#include <gtest/gtest.h>
#include <fstream>

#include "Readers/CsvReader.hpp"

namespace SageParserTest
{

    class CsvReaderTest : public ::testing::Test
    {
    protected:
        std::filesystem::path tempFilePath;
        char delimiter = ',';

        void SetUp() override
        {
            // Create a temporary file path
            tempFilePath = std::filesystem::temp_directory_path() / "test.csv";

            // Setup a minimal CSV content
            std::ofstream ofs(tempFilePath);
            ofs << "ID,Name\n1,John Doe\n2,Jane Doe";
            ofs.close();
        }

        void TearDown() override
        {
            // Clean up the temporary file
            std::filesystem::remove(tempFilePath);
        }
    };

    TEST_F(CsvReaderTest, ReadsValidCsvSuccessfully)
    {
        SageParser::CsvReader reader(tempFilePath, delimiter);
        auto table = reader.read();

        // Check that the table is not null
        ASSERT_NE(table, nullptr);

        // Check the number of columns is correct
        auto columnNames = table->columnNames();
        EXPECT_EQ(columnNames.size(), 2) << "Table should have exactly 2 columns.";

        // Check that the column names are correct
        EXPECT_TRUE(std::find(columnNames.begin(), columnNames.end(), "ID") != columnNames.end()) << "Column 'ID' not found.";
        EXPECT_TRUE(std::find(columnNames.begin(), columnNames.end(), "Name") != columnNames.end()) << "Column 'Name' not found.";

        // Check the number of entries in each column
        for (const auto &columnName : columnNames)
        {
            EXPECT_EQ(table->at(columnName).size(), 2) << "Column '" << columnName << "' should have exactly 2 entries.";
        }

        // Check the content of the table
        EXPECT_EQ((*table)["ID"][0], "1") << "First entry of 'ID' column should be '1'.";
        EXPECT_EQ((*table)["ID"][1], "2") << "Second entry of 'ID' column should be '2'.";
        EXPECT_EQ((*table)["Name"][0], "John Doe") << "First entry of 'Name' column should be 'John Doe'.";
        EXPECT_EQ((*table)["Name"][1], "Jane Doe") << "Second entry of 'Name' column should be 'Jane Doe'.";
    }

    TEST_F(CsvReaderTest, ThrowsWhenFileNotFound)
    {
        std::filesystem::path invalidPath = "nonexistent.csv";
        SageParser::CsvReader reader(invalidPath, delimiter);

        EXPECT_THROW(
            {
                reader.read();
            },
            std::invalid_argument);
    }
}
