#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <map>
#include <memory>

#include "Readers/CsvReader.hpp"
#include "Readers/XmlReader.hpp"
#include "Writers/CsvWriter.hpp"
#include "Writers/XmlWriter.hpp"

namespace SageParserTest
{
    using namespace SageParser;

    class DataIntegrityTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            csvPath = std::filesystem::temp_directory_path()
                / "sageparser_data_integrity.csv";
            xmlPath = std::filesystem::temp_directory_path()
                / "sageparser_data_integrity.xml";
        }

        void TearDown() override
        {
            std::filesystem::remove(csvPath);
            std::filesystem::remove(xmlPath);
        }

        std::filesystem::path csvPath;
        std::filesystem::path xmlPath;
    };

    TEST_F(DataIntegrityTest, CsvRoundTripPreservesSpecialCharacters)
    {
        auto source = std::make_shared<Table>();
        source->addColumn("ID");
        source->addColumn("Description");
        source->addColumn("Notes");
        source->addRow({{"ID", "1"},
                        {"Description", "washer, large"},
                        {"Notes", "quoted \"value\"\nsecond line"}});
        source->addRow({{"ID", "2"},
                        {"Description", "UTF-8: Тест"},
                        {"Notes", ""}});

        CsvWriter(csvPath, ',', false).write(source);
        const auto result = CsvReader(csvPath).read();

        ASSERT_EQ(result->columnNamesMap(), source->columnNamesMap());
        ASSERT_EQ(result->rowCount(), source->rowCount());
        for (std::size_t row = 0; row < source->rowCount(); ++row)
        {
            for (std::size_t column = 0; column < source->columnCount(); ++column)
            {
                EXPECT_EQ(result->at(static_cast<int>(row), static_cast<int>(column)),
                          source->at(static_cast<int>(row), static_cast<int>(column)));
            }
        }
    }

    TEST_F(DataIntegrityTest, CsvRoundTripPreservesHeaderOnlyTable)
    {
        auto source = std::make_shared<Table>();
        source->addColumn("ID");
        source->addColumn("Name");

        CsvWriter(csvPath).write(source);
        const auto result = CsvReader(csvPath).read();

        EXPECT_EQ(result->columnNamesMap(), source->columnNamesMap());
        EXPECT_EQ(result->rowCount(), 0);
    }

    TEST_F(DataIntegrityTest, XmlRoundTripPreservesEscapedAndUtf8Values)
    {
        auto source = std::make_shared<Table>();
        source->addColumn("ID");
        source->addColumn("Name");
        source->addRow({{"ID", "1"}, {"Name", "Олива & <filter>"}});

        XmlWriter(xmlPath).write(source);
        const auto result = XmlReader(xmlPath).read();

        EXPECT_EQ(result->columnNamesMap(), source->columnNamesMap());
        EXPECT_EQ(result->rowCount(), 1);
        EXPECT_EQ(result->at(0, "Name"), "Олива & <filter>");
    }

    TEST_F(DataIntegrityTest, XmlReaderUsesColumnsFromEveryRow)
    {
        std::ofstream output(xmlPath);
        output << "<Root><Row><A>one</A></Row><Row><B>two</B></Row></Root>";
        output.close();

        const auto result = XmlReader(xmlPath).read();
        ASSERT_EQ(result->columnCount(), 2);
        EXPECT_EQ(result->at(0, "A"), "one");
        EXPECT_EQ(result->at(0, "B"), "");
        EXPECT_EQ(result->at(1, "A"), "");
        EXPECT_EQ(result->at(1, "B"), "two");
    }

    TEST_F(DataIntegrityTest, XmlRejectsAmbiguousOrUnwritableTables)
    {
        {
            std::ofstream output(xmlPath);
            output << "<Root><Row><A>one</A><A>two</A></Row></Root>";
        }
        EXPECT_THROW(XmlReader(xmlPath).read(), std::runtime_error);

        auto invalidName = std::make_shared<Table>();
        invalidName->addColumn("not valid");
        invalidName->addRow({{"not valid", "value"}});
        EXPECT_THROW(XmlWriter(xmlPath).write(invalidName), std::invalid_argument);

        auto empty = std::make_shared<Table>();
        empty->addColumn("Name");
        EXPECT_THROW(XmlWriter(xmlPath).write(empty), std::invalid_argument);
    }

    TEST_F(DataIntegrityTest, WritersRejectNullTables)
    {
        EXPECT_THROW(CsvWriter(csvPath).write(nullptr), std::invalid_argument);
        EXPECT_THROW(XmlWriter(xmlPath).write(nullptr), std::invalid_argument);

        auto noColumns = std::make_shared<Table>();
        noColumns->addRow(std::map<std::string, std::string> {});
        EXPECT_THROW(CsvWriter(csvPath).write(noColumns), std::invalid_argument);
        EXPECT_THROW(XmlWriter(xmlPath).write(noColumns), std::invalid_argument);
    }
} // namespace SageParserTest
