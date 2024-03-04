#include <gtest/gtest.h>

#include <fstream>
#include <filesystem>

#include <pugixml.hpp>

#include "Writers/XmlWriter.hpp"
#include "Table.hpp"

namespace SageParserTest
{
    using namespace SageParser;

    class XmlWriterTest : public ::testing::Test
    {
    protected:
        std::filesystem::path tempFilePath;
        std::shared_ptr<Table> table;

        void SetUp() override
        {
            tempFilePath = std::filesystem::temp_directory_path() / "output_test.xml";
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

    TEST_F(XmlWriterTest, WriteTableToFile)
    {
        XmlWriter writer(tempFilePath);
        writer.write(table);

        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(tempFilePath.c_str());
        ASSERT_TRUE(result) << "Failed to parse XML file.";

        // Verify root node exists
        auto root = doc.child("Root");
        ASSERT_TRUE(root) << "Root element not found.";

        // Verify the number of Row elements
        size_t rowCount = std::distance(root.children("Row").begin(), root.children("Row").end());
        EXPECT_EQ(rowCount, 2) << "XML file should have 2 Row elements.";

        // Verify content of each Row
        size_t rowIndex = 0;
        for (pugi::xml_node row : root.children("Row"))
        {
            auto idNode = row.child("ID");
            auto nameNode = row.child("Name");

            ASSERT_TRUE(idNode) << "ID node not found in row " << rowIndex;
            ASSERT_TRUE(nameNode) << "Name node not found in row " << rowIndex;

            std::string expectedId = std::to_string(rowIndex + 1);
            std::string expectedName = rowIndex == 0 ? "John Doe" : "Jane Doe";

            EXPECT_EQ(idNode.text().as_string(), expectedId) << "ID value does not match at row " << rowIndex;
            EXPECT_EQ(nameNode.text().as_string(), expectedName) << "Name value does not match at row " << rowIndex;

            ++rowIndex;
        }
    }

} // namespace SageParserTest
