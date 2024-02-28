#include <gtest/gtest.h>

#include "DataProcessorFactory.cpp"
#include "DataProcessors/DefaultTableProcessor.cpp"
#include "DataProcessors/OmegaPricelistProcessor.cpp"

#include "ReaderFactory.hpp"
#include "Readers/CsvReader.hpp"
// #include "Readers/XmlReader.hpp"

#include "WriterFactory.hpp"
#include "Writers/CsvWriter.hpp"
#include "Writers/XmlWriter.hpp"

std::string getResourcePath(const std::string &relativePath)
{
    return std::string(TEST_RESOURCES_DIR) + "/" + relativePath;
}

TEST(DataProcessorFactoryTest, ProperObjectIsCreated)
{
    auto processor = SageParser::DataProcessorFactory::createDataProcessor(SageParser::DocType::SIMPLE_Table);
    ASSERT_NE(nullptr, processor);
    EXPECT_EQ(typeid(SageParser::DefaultTableProcessor), typeid(*processor));
}

TEST(SageParserLibTest, MinimalCsvWorkCycle)
{
    // 1. Read data from file
    auto reader = SageParser::ReaderFactory::createReader(SageParser::ReaderFileType::CSV);
    reader->setFilePath(getResourcePath("input_testMinimalCsvWorkCycle.csv"));
    dynamic_cast<SageParser::CsvReader *>(reader.get())->setDelimiter('|');
    std::shared_ptr<SageParser::Table> inputTable;
    EXPECT_NO_THROW(inputTable = reader->read());
    EXPECT_EQ(inputTable->columnNames, std::vector<std::string>({"NAMEUKR", "Count", "Unit", "CENA"}));
    EXPECT_EQ(inputTable->dataRows.at(0), std::vector<std::string>({"Ім'я", "2", "шт", "123,10"}));

    // 2. Process data
    auto processor = SageParser::DataProcessorFactory::createDataProcessor(SageParser::DocType::SIMPLE_Table);
    std::shared_ptr<SageParser::Table> outputTable;
    EXPECT_NO_THROW(outputTable = processor->process(inputTable));
    EXPECT_EQ(outputTable->columnNames, std::vector<std::string>({"name", "count", "unit", "price"}));
    EXPECT_EQ(outputTable->dataRows.at(0), std::vector<std::string>({"Ім'я", "2", "шт.", "123,10"}));

    // 3. Write data
    auto writer = SageParser::WriterFactory::createWriter(SageParser::WriterFileType::CSV);
    writer->setFilePath(getResourcePath("output_testMinimalCsvWorkCycle.csv"));
    EXPECT_NO_THROW(writer->write(outputTable));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
