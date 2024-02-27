#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

#include "Readers/XmlReader.hpp"
#include "Writers/XmlWriter.hpp"
#include "DataTable.hpp"

std::filesystem::path CreateTempDirectory()
{
    std::filesystem::path temp_dir = std::filesystem::temp_directory_path() / "XmlTests";
    std::filesystem::create_directories(temp_dir);
    return temp_dir;
}

std::shared_ptr<SageParser::DataTable> CreateSampleDataTable()
{
    auto DataTable = std::make_shared<SageParser::DataTable>();

    DataTable->columnNames = {"Column1", "Column2", "Column3"};
    DataTable->dataRows = {
        {"Row1Col1", "Row1Col2", "Row1Col3"},
        {"Row2Col1", "Row2Col2", "Row2Col3"},
    };

    return DataTable;
}

class XmlWriterReaderTest : public ::testing::Test
{
protected:
    std::filesystem::path temp_dir;
    std::shared_ptr<SageParser::XmlWriter> writer;
    std::shared_ptr<SageParser::XmlReader> reader;
    std::shared_ptr<SageParser::DataTable> DataTable;

    void SetUp() override
    {
        temp_dir = CreateTempDirectory();
        writer = std::make_shared<SageParser::XmlWriter>();
        reader = std::make_shared<SageParser::XmlReader>();
        DataTable = CreateSampleDataTable();
    }

    void TearDown() override
    {
        std::filesystem::remove_all(temp_dir); // Clean up the temporary directory
    }
};

TEST_F(XmlWriterReaderTest, XmlWriteReadCycle)
{
    auto file_path = temp_dir / "test.csv";
    writer->setFilePath(file_path);
    writer->write(DataTable);

    ASSERT_TRUE(std::filesystem::exists(file_path));

    reader->setFilePath(file_path);
    auto read_DataTable = reader->read();

    ASSERT_EQ(read_DataTable->columnNames, DataTable->columnNames);
    ASSERT_EQ(read_DataTable->dataRows, DataTable->dataRows);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}