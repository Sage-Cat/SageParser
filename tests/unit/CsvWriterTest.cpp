#include <gtest/gtest.h>

#include <fstream>
#include <filesystem>

#include "Writers/CsvWriter.hpp"

#include "Parsing.hpp"

namespace SageParserTest
{
    using namespace SageParser;

    class CsvWriterTest : public ::testing::Test
    {
    protected:
        std::filesystem::path tempFilePath;
        std::shared_ptr<Table> table;

        void SetUp() override
        {
            tempFilePath = std::filesystem::temp_directory_path() / "output_test.csv";
            table = std::make_shared<Table>();

            // Add columns to the table
            table->addColumn("ID");
            table->addColumn("Name");

            // Add rows to the table
            table->addRow({{"ID", "1"}, {"Name", "John Doe"}});
            table->addRow({{"ID", "2"}, {"Name", "Jane Doe"}});
        }

        void TearDown() override
        {
            std::filesystem::remove(tempFilePath);
        }
    };

    TEST_F(CsvWriterTest, WriteTableToFile)
    {
        CsvWriter writer(tempFilePath, ',', false);
        writer.write(table);

        std::ifstream file(tempFilePath);
        ASSERT_TRUE(file.is_open());

        std::string line;
        std::vector<std::string> lines;
        while (getline(file, line))
            lines.push_back(line);

        ASSERT_EQ(lines.size(), 3) << "CSV file should have a header and 2 rows.";

        auto header = parseCsvLine(lines[0]);
        std::vector<std::string> expectedHeader{"ID", "Name"};
        ASSERT_EQ(header.size(), expectedHeader.size()) << "CSV header does not contain the correct number of columns.";
        for (size_t i = 0; i < expectedHeader.size(); ++i)
        {
            EXPECT_EQ(header[i], expectedHeader[i]) << "Column order or name does not match at index " << i;
        }

        // Validate the first data row
        auto firstRow = parseCsvLine(lines[1]);
        std::vector<std::string> expectedFirstRow{"1", "John Doe"};
        ASSERT_EQ(firstRow.size(), expectedFirstRow.size()) << "First row does not have the correct number of columns.";
        for (size_t i = 0; i < expectedFirstRow.size(); ++i)
        {
            EXPECT_EQ(firstRow[i], expectedFirstRow[i]) << "Data in first row does not match at index " << i;
        }

        // Validate the second data row
        auto secondRow = parseCsvLine(lines[2]);
        std::vector<std::string> expectedSecondRow{"2", "Jane Doe"};
        ASSERT_EQ(secondRow.size(), expectedSecondRow.size()) << "Second row does not have the correct number of columns.";
        for (size_t i = 0; i < expectedSecondRow.size(); ++i)
        {
            EXPECT_EQ(secondRow[i], expectedSecondRow[i]) << "Data in second row does not match at index " << i;
        }
    }

} // namespace SageParserTest
