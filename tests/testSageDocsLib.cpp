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
    auto processor = SageDocs::DataProcessorFactory::createDataProcessor(SageDocs::DocType::SIMPLE_TABLE);
    ASSERT_NE(nullptr, processor);
    EXPECT_EQ(typeid(SageDocs::SimpleTableProcessor), typeid(*processor));
}

TEST(SageDocsLibTest, MinimalCsvWorkCycle)
{
    // 1. Read data from file
    auto reader = SageDocs::ReaderFactory::createReader(SageDocs::ReaderFileType::CSV);
    reader->setFilePath(getResourcePath("input_testMinimalCsvWorkCycle.csv"));
    dynamic_cast<SageDocs::CsvReader *>(reader.get())->setDelimiter('|');
    std::shared_ptr<SageDocs::Dataset> inputDataset;
    EXPECT_NO_THROW(inputDataset = reader->readData());
    EXPECT_EQ(inputDataset->columnNames, std::vector<std::string>({"NAMEUKR", "Count", "Unit", "CENA"}));
    EXPECT_EQ(inputDataset->dataRows.at(0), std::vector<std::string>({"Ім'я", "2", "шт", "123,10"})); // Assuming the decimal separator is '.'

    // 2. Process data
    auto processor = SageDocs::DataProcessorFactory::createDataProcessor(SageDocs::DocType::SIMPLE_TABLE);
    std::shared_ptr<SageDocs::Dataset> outputDataset;
    EXPECT_NO_THROW(outputDataset = processor->process(inputDataset));
    EXPECT_EQ(outputDataset->columnNames, std::vector<std::string>({"name", "count", "unit", "price"}));
    EXPECT_EQ(outputDataset->dataRows.at(0), std::vector<std::string>({"Ім'я", "2", "шт.", "123,10"}));

    // 3. Write data
    auto writer = SageDocs::WriterFactory::createWriter(SageDocs::WriterFileType::CSV);
    writer->setFilePath(getResourcePath("output_testMinimalCsvWorkCycle.csv"));
    EXPECT_NO_THROW(writer->writeData(outputDataset));
}

TEST(SageDocsLibTest, MinimalXmlWorkCycle)
{
    // read the data
    auto reader = SageDocs::ReaderFactory::createReader(SageDocs::ReaderFileType::XML);
    reader->setFilePath(getResourcePath("input_testMinimalXmlWorkCycle.xml"));
    std::shared_ptr<SageDocs::Dataset> inputDataset;
    EXPECT_NO_THROW(inputDataset = reader->readData());
    EXPECT_EQ(inputDataset->columnNames, std::vector<std::string>({"KART", "NAIMUKR", "MINCENA", "CENAPART", "BAZED", "IMPORT", "KART", "NAIMUKR", "MINCENA", "CENAPART", "BAZED", "IMPORT", "KART", "NAIMUKR", "MINCENA", "CENAPART", "BAZED", "IMPORT"}));
    EXPECT_EQ(inputDataset->dataRows.at(0), std::vector<std::string>({"3887946917", "Підшипник 7615 (32315)", "935,10", "889,08", "шт.", "True", "69001280801", "Сальник КПП", "421,08", "387,00", "шт.", "True", "69001290859", "фільтр АКПП", "2738,46", "2745,36", "шт.", "True"}));
    // EXPECT_EQ(inputDataset->columnNames, std::vector<std::string>({"KART", "NAIMUKR", "MINCENA", "CENAPART", "BAZED"}));
    // EXPECT_EQ(inputDataset->dataRows.at(0), std::vector<std::string>({"3887946917", "Підшипник 7615 (32315)", "935,10", "889,08", "шт."}));

    // 2. Process data
    auto processor = SageDocs::DataProcessorFactory::createDataProcessor(SageDocs::DocType::OMEGA_XMLPRICELIST);
    std::shared_ptr<SageDocs::Dataset> outputDataset;
    EXPECT_NO_THROW(outputDataset = processor->process(inputDataset));
    EXPECT_EQ(outputDataset->columnNames, std::vector<std::string>({"id", "name", "price", "price", "unit", "import", "id", "name", "price", "price", "unit", "import", "id", "name", "price", "price", "unit", "import"}));
    EXPECT_EQ(outputDataset->dataRows.at(0), std::vector<std::string>({"3887946917", "Підшипник 7615 (32315)", "935,10", "889,08", "шт.", "True", "69001280801", "Сальник КПП", "421,08", "387,00", "шт.", "True", "69001290859", "фільтр АКПП", "2738,46", "2745,36", "шт.", "True"}));

    // 3. Write data
    auto writer = SageDocs::WriterFactory::createWriter(SageDocs::WriterFileType::XML);
    writer->setFilePath(getResourcePath("output_testMinimalXmlWorkCycle.xml"));
    EXPECT_NO_THROW(writer->writeData(outputDataset));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
