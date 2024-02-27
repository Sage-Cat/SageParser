#include <gtest/gtest.h>

#include "DataProcessorFactory.cpp"
#include "DataProcessors/SimpleTableProcessor.cpp"
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
    auto processor = SageParser::DataProcessorFactory::createDataProcessor(SageParser::DocType::SIMPLE_TABLE);
    ASSERT_NE(nullptr, processor);
    EXPECT_EQ(typeid(SageParser::SimpleTableProcessor), typeid(*processor));
}

TEST(SageParserLibTest, MinimalCsvWorkCycle)
{
    // 1. Read data from file
    auto reader = SageParser::ReaderFactory::createReader(SageParser::ReaderFileType::CSV);
    reader->setFilePath(getResourcePath("input_testMinimalCsvWorkCycle.csv"));
    dynamic_cast<SageParser::CsvReader *>(reader.get())->setDelimiter('|');
    std::shared_ptr<SageParser::Table> inputTable;
    EXPECT_NO_THROW(inputTable = reader->readData());
    EXPECT_EQ(inputTable->columnNames, std::vector<std::string>({"NAMEUKR", "Count", "Unit", "CENA"}));
    EXPECT_EQ(inputTable->dataRows.at(0), std::vector<std::string>({"Ім'я", "2", "шт", "123,10"})); // Assuming the decimal separator is '.'

    // 2. Process data
    auto processor = SageParser::DataProcessorFactory::createDataProcessor(SageParser::DocType::SIMPLE_TABLE);
    std::shared_ptr<SageParser::Table> outputTable;
    EXPECT_NO_THROW(outputTable = processor->process(inputTable));
    EXPECT_EQ(outputTable->columnNames, std::vector<std::string>({"name", "count", "unit", "price"}));
    EXPECT_EQ(outputTable->dataRows.at(0), std::vector<std::string>({"Ім'я", "2", "шт.", "123,10"}));

    // 3. Write data
    auto writer = SageParser::WriterFactory::createWriter(SageParser::WriterFileType::CSV);
    writer->setFilePath(getResourcePath("output_testMinimalCsvWorkCycle.csv"));
    EXPECT_NO_THROW(writer->writeData(outputTable));
}

TEST(SageParserLibTest, MinimalXmlWorkCycle)
{
    // read the data
    auto reader = SageParser::ReaderFactory::createReader(SageParser::ReaderFileType::XML);
    reader->setFilePath(getResourcePath("input_testMinimalXmlWorkCycle.xml"));
    std::shared_ptr<SageParser::Table> inputTable;
    EXPECT_NO_THROW(inputTable = reader->readData());
    EXPECT_EQ(inputTable->columnNames, std::vector<std::string>({"KART", "NAIMUKR", "MINCENA", "CENAPART", "BAZED", "IMPORT", "KART", "NAIMUKR", "MINCENA", "CENAPART", "BAZED", "IMPORT", "KART", "NAIMUKR", "MINCENA", "CENAPART", "BAZED", "IMPORT"}));
    EXPECT_EQ(inputTable->dataRows.at(0), std::vector<std::string>({"3887946917", "Підшипник 7615 (32315)", "935,10", "889,08", "шт.", "True", "69001280801", "Сальник КПП", "421,08", "387,00", "шт.", "True", "69001290859", "фільтр АКПП", "2738,46", "2745,36", "шт.", "True"}));
    // EXPECT_EQ(inputTable->columnNames, std::vector<std::string>({"KART", "NAIMUKR", "MINCENA", "CENAPART", "BAZED"}));
    // EXPECT_EQ(inputTable->dataRows.at(0), std::vector<std::string>({"3887946917", "Підшипник 7615 (32315)", "935,10", "889,08", "шт."}));

    // 2. Process data
    auto processor = SageParser::DataProcessorFactory::createDataProcessor(SageParser::DocType::OMEGA_XMLPRICELIST);
    std::shared_ptr<SageParser::Table> outputTable;
    EXPECT_NO_THROW(outputTable = processor->process(inputTable));
    EXPECT_EQ(outputTable->columnNames, std::vector<std::string>({"id", "name", "price", "price", "unit", "import", "id", "name", "price", "price", "unit", "import", "id", "name", "price", "price", "unit", "import"}));
    EXPECT_EQ(outputTable->dataRows.at(0), std::vector<std::string>({"3887946917", "Підшипник 7615 (32315)", "935,10", "889,08", "шт.", "True", "69001280801", "Сальник КПП", "421,08", "387,00", "шт.", "True", "69001290859", "фільтр АКПП", "2738,46", "2745,36", "шт.", "True"}));

    // 3. Write data
    auto writer = SageParser::WriterFactory::createWriter(SageParser::WriterFileType::XML);
    writer->setFilePath(getResourcePath("output_testMinimalXmlWorkCycle.xml"));
    EXPECT_NO_THROW(writer->writeData(outputTable));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
