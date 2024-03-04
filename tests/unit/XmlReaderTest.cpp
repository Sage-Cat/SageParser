#include <gtest/gtest.h>

#include <fstream>
#include <filesystem>

#include "Readers/XmlReader.hpp"

namespace SageParserTest
{
    using namespace SageParser;

    class XmlReaderTest : public ::testing::Test
    {
    protected:
        std::filesystem::path tempFilePath;

        void SetUp() override
        {
            tempFilePath = std::filesystem::temp_directory_path() / "test.xml";

            // Setup a minimal XML content
            std::ofstream ofs(tempFilePath);
            ofs << R"(<Root>
                    <Row>
                        <ID>1</ID>
                        <Name>John Doe</Name>
                    </Row>
                    <Row>
                        <ID>2</ID>
                        <Name>Jane Doe</Name>
                    </Row>
                  </Root>)";
            ofs.close();
        }

        void TearDown() override
        {
            std::filesystem::remove(tempFilePath);
        }
    };

    TEST_F(XmlReaderTest, ReadTableFromFile)
    {
        XmlReader reader(tempFilePath);
        auto table = reader.read();

        // Check that the table is not null
        ASSERT_NE(table, nullptr);

        // Check the number of columns and rows is correct
        EXPECT_EQ(table->columnCount(), 2) << "Table should have exactly 2 columns.";
        EXPECT_EQ(table->rowCount(), 2) << "Table should have exactly 2 rows.";

        // Check that the column names are correct
        auto columnNamesMap = table->columnNamesMap();
        EXPECT_NE(columnNamesMap.find(0), columnNamesMap.end()) << "Column 'ID' not found.";
        EXPECT_NE(columnNamesMap.find(1), columnNamesMap.end()) << "Column 'Name' not found.";
        EXPECT_EQ(columnNamesMap.at(0), "ID") << "First column should be 'ID'.";
        EXPECT_EQ(columnNamesMap.at(1), "Name") << "Second column should be 'Name'.";

        // Check the content of the table
        EXPECT_EQ(table->at(0, "ID"), "1") << "First entry of 'ID' column should be '1'.";
        EXPECT_EQ(table->at(1, "ID"), "2") << "Second entry of 'ID' column should be '2'.";
        EXPECT_EQ(table->at(0, "Name"), "John Doe") << "First entry of 'Name' column should be 'John Doe'.";
        EXPECT_EQ(table->at(1, "Name"), "Jane Doe") << "Second entry of 'Name' column should be 'Jane Doe'.";
    }

    TEST_F(XmlReaderTest, ThrowWhenFileNotFound)
    {
        std::filesystem::path invalidPath = "nonexistent.xml";
        XmlReader reader(invalidPath);

        EXPECT_THROW(
            {
                reader.read();
            },
            std::runtime_error);
    }

} // namespace SageParserTest
