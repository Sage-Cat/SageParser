#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include "Writers/CsvWriter.hpp"

namespace SageParserTest
{

    class CsvWriterTest : public ::testing::Test
    {
    protected:
        std::filesystem::path tempFilePath;
        std::shared_ptr<SageParser::Table> table;

        void SetUp() override
        {
            tempFilePath = std::filesystem::temp_directory_path() / "output_test.csv";
            table = std::make_shared<SageParser::Table>();
            (*table)["ID"] = {"1", "2"};
            (*table)["Name"] = {"John Doe", "Jane Doe"};
        }

        void TearDown() override
        {
            std::filesystem::remove(tempFilePath);
        }

        std::unordered_set<std::string> parserCsvLine(const std::string &line)
        {
            std::unordered_set<std::string> values;
            std::stringstream lineStream(line);
            std::string cell;

            while (std::getline(lineStream, cell, ','))
            {
                auto start = cell.find_first_of('"') + 1;
                auto end = cell.find_last_of('"');
                if (start < end)
                {
                    values.insert(cell.substr(start, end - start));
                }
            }

            return values;
        }
    };

    TEST_F(CsvWriterTest, WritesTableToCsvSuccessfully)
    {
        SageParser::CsvWriter writer(tempFilePath);
        writer.write(table);

        std::ifstream file(tempFilePath);
        std::string line;
        std::vector<std::string> lines;

        while (getline(file, line))
        {
            lines.push_back(line);
        }

        ASSERT_EQ(lines.size(), 3) << "CSV file should have a header and 2 rows.";

        auto header = parserCsvLine(lines[0]);
        std::unordered_set<std::string> expectedHeader{"ID", "Name"};
        EXPECT_EQ(header, expectedHeader) << "CSV header does not contain the expected columns.";

        auto firstRow = parserCsvLine(lines[1]);
        std::unordered_set<std::string> expectedFirstRow{"1", "John Doe"};
        EXPECT_EQ(firstRow, expectedFirstRow) << "First row does not match expected data.";

        auto secondRow = parserCsvLine(lines[2]);
        std::unordered_set<std::string> expectedSecondRow{"2", "Jane Doe"};
        EXPECT_EQ(secondRow, expectedSecondRow) << "Second row does not match expected data.";
    }
}
