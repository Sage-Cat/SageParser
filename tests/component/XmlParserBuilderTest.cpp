#include <gtest/gtest.h>

#include <fstream>

#include <pugixml.hpp>

#include "ParserBuilder.hpp"
#include "Readers/XmlReader.hpp"
#include "Processors/DefaultTableProcessor.hpp"
#include "Writers/XmlWriter.hpp"

namespace SageParserTest
{
    using namespace SageParser;

    class XmlParserBuilderTest : public ::testing::Test
    {
    protected:
        std::filesystem::path tempInputPath_;
        std::filesystem::path tempOutputPath_;

        void SetUp() override
        {
            tempInputPath_ = std::filesystem::temp_directory_path() / "temp_input.xml";
            std::ofstream inputFile(tempInputPath_, std::ios::binary);
            inputFile << R"(<?xml version="1.0" encoding="UTF-8"?>
<Root>
    <Прайс>
        <KART>6900855972</KART>
        <KODKAT>7.5683</KODKAT>
        <KODTNVED>нет</KODTNVED>
        <NAIM>Термовыключатель</NAIM>
        <NAIMUKR>Термовимикач</NAIMUKR>
        <CENAPART>699,30</CENAPART>
        <MINCENA>697,50</MINCENA>
        <ROZNCENA>837,00</ROZNCENA>
        <BAZED>шт.</BAZED>
        <STOCK>0</STOCK>
        <IMPORT>True</IMPORT>
    </Прайс>
</Root>)";
            inputFile.close();

            tempOutputPath_ = std::filesystem::temp_directory_path() / "temp_output.xml";
        }

        void TearDown() override
        {
            std::filesystem::remove(tempInputPath_);
            // std::filesystem::remove(tempOutputPath_);
        }
    };

    TEST_F(XmlParserBuilderTest, XmlRoutine)
    {
        auto reader = std::make_unique<XmlReader>(tempInputPath_);
        auto writer = std::make_unique<XmlWriter>(tempOutputPath_);

        std::vector<std::unique_ptr<IProcessor>> processors;
        processors.push_back(std::make_unique<DefaultTableProcessor>());

        ParserBuilder builder;
        builder.setReader(std::move(reader));
        builder.setProcessors(std::move(processors));
        builder.setWriter(std::move(writer));
        builder.performOperation();

        // Load the output XML to verify its structure and content
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(tempOutputPath_.c_str());
        ASSERT_TRUE(result) << "Failed to parse XML output file.";

        auto root = doc.child("Root");
        ASSERT_TRUE(root) << "Root element not found.";

        // Print the actual content of the file for debugging
        // std::ostringstream oss;
        // doc.print(oss);
        // std::string xmlContent = oss.str();
        // std::cout << "Actual XML content:\n"
        //           << xmlContent << "\n";

        size_t rowCount = 0;
        for (auto &price : root.children("Row"))
            ++rowCount;
        EXPECT_EQ(rowCount, 1) << "Expected one processed record elements.";

        auto row = root.first_child();
        EXPECT_EQ(std::string(row.child(Default::ColumnNames::NAME.data()).text().as_string()), "Термовимикач") << "Name value does not match";
        EXPECT_EQ(std::string(row.child(Default::ColumnNames::UNIT.data()).text().as_string()), Default::Units::PIECE) << "Unit value does not match";
        EXPECT_EQ(std::string(row.child(Default::ColumnNames::PRICE.data()).text().as_string()), "697,50") << "Price value does not match";
    }

} // namespace SageParserTest
