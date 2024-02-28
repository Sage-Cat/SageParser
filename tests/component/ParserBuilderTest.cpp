#include <gtest/gtest.h>
#include <fstream>
#include "ParserBuilder.hpp"
#include "Readers/CsvReader.hpp"
#include "Processors/DefaultTableProcessor.hpp"
#include "Writers/CsvWriter.hpp"
#include "Parsing.hpp"

namespace SageParserTest
{
    using namespace SageParser;

    class ParserBuilderTest : public ::testing::Test
    {
    protected:
        std::filesystem::path tempInputPath_;
        std::filesystem::path tempOutputPath_;

        void SetUp() override
        {
            // Create and populate a temporary input CSV file
            tempInputPath_ = std::filesystem::temp_directory_path() / "temp_input.csv";
            std::ofstream inputFile(tempInputPath_);
            inputFile << "NAME,Count,Unit,PRICE\n";
            inputFile << "Tire for DAF,10,шт,2.50\n";
            inputFile << "Oil for DAF,5,бочк,3.00\n";
            inputFile.close();

            tempOutputPath_ = std::filesystem::temp_directory_path() / "temp_output.csv";
        }

        void TearDown() override
        {
            std::filesystem::remove(tempInputPath_);
            std::filesystem::remove(tempOutputPath_);
        }
    };

    TEST_F(ParserBuilderTest, CsvRoutine)
    {
        auto reader = std::make_unique<CsvReader>(tempInputPath_, ',');
        auto writer = std::make_unique<CsvWriter>(tempOutputPath_, ',', false);

        std::vector<std::unique_ptr<IProcessor>> processors;
        processors.push_back(std::make_unique<DefaultTableProcessor>());

        ParserBuilder builder;
        builder.setReader(std::move(reader));
        builder.setProcessors(std::move(processors));
        builder.setWriter(std::move(writer));
        builder.performOperation();

        std::ifstream file(tempOutputPath_);
        ASSERT_TRUE(file.is_open());

        std::string line;
        std::vector<std::string> lines;
        while (getline(file, line))
        {
            lines.push_back(line);
        }

        ASSERT_GT(lines.size(), 0) << "Output CSV should have at least one line of output.";

        // HEADERS CHECK
        auto header = parseCsvLine(lines.front());
        std::vector<std::string> expectedHeader{
            Default::ColumnNames::NAME.data(),
            Default::ColumnNames::COUNT.data(),
            Default::ColumnNames::UNIT.data(),
            Default::ColumnNames::PRICE.data()};

        ASSERT_EQ(header.size(), expectedHeader.size()) << "CSV header does not contain the correct number of columns.";
        for (size_t i = 0; i < expectedHeader.size(); ++i)
        {
            EXPECT_EQ(header[i], expectedHeader[i]) << "Column order or name does not match header=" << header[i] << " expected=" << expectedHeader[i];
        }

        // UNITS CHECK
        auto unitIndex = std::distance(header.begin(), std::find(header.begin(), header.end(), Default::ColumnNames::UNIT.data()));
        ASSERT_NE(unitIndex, header.size()) << "Unit column not found in the header.";

        // Verify each row's "Unit" value
        std::vector<std::string> expectedUnits{
            Default::Units::PIECE.data(),
            Default::Units::BARREL.data()};
        for (size_t rowIndex = 1 /* skip header */; rowIndex < lines.size(); ++rowIndex)
        {
            auto row = parseCsvLine(lines[rowIndex]);
            ASSERT_LT(unitIndex, row.size()) << "Row " << rowIndex << " does not have a Unit value.";
            EXPECT_EQ(row[unitIndex], expectedUnits[rowIndex - 1]) << "Unit value does not match at row " << rowIndex;
        }
    }

} // namespace SageParser
