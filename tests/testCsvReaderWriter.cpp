#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

#include "Readers/CsvReader.hpp"
#include "Writers/CsvWriter.hpp"
#include "Table.hpp"

std::filesystem::path CreateTempDirectory()
{
    std::filesystem::path temp_dir = std::filesystem::temp_directory_path() / "CsvTests";
    std::filesystem::create_directories(temp_dir);
    return temp_dir;
}

std::shared_ptr<SageParser::Table> CreateSampleTable()
{
    auto Table = std::make_shared<SageParser::Table>();

    Table->columnNames = {"Column1", "Column2", "Column3"};
    Table->dataRows = {
        {"Row1Col1", "Row1Col2", "Row1Col3"},
        {"Row2Col1", "Row2Col2", "Row2Col3"},
    };

    return Table;
}

class CsvWriterReaderTest : public ::testing::Test
{
protected:
    std::filesystem::path temp_dir;
    std::shared_ptr<SageParser::CsvWriter> writer;
    std::shared_ptr<SageParser::CsvReader> reader;
    std::shared_ptr<SageParser::Table> Table;

    void SetUp() override
    {
        temp_dir = CreateTempDirectory();
        writer = std::make_shared<SageParser::CsvWriter>();
        reader = std::make_shared<SageParser::CsvReader>();
        Table = CreateSampleTable();
    }

    void TearDown() override
    {
        std::filesystem::remove_all(temp_dir); // Clean up the temporary directory
    }
};

TEST_F(CsvWriterReaderTest, WriteReadCycle)
{
    auto file_path = temp_dir / "test.csv";
    writer->setFilePath(file_path);
    writer->writeData(Table);

    ASSERT_TRUE(std::filesystem::exists(file_path));

    reader->setFilePath(file_path);
    auto read_Table = reader->readData();

    ASSERT_EQ(read_Table->columnNames, Table->columnNames);
    ASSERT_EQ(read_Table->dataRows, Table->dataRows);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
