#include <gtest/gtest.h>

#include "DataProcessorFactory.cpp"
#include "DataProcessors/SimpleTableProcessor.cpp"

#include "ReaderFactory.hpp"
#include "Readers/CsvReader.hpp"

#include "WriterFactory.hpp"
#include "Writers/CsvWriter.hpp"

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
    reader->setFileName("input_testMinimalCsvWorkCycle.csv");
    std::shared_ptr<SageDocs::Dataset> inputDataset;
    EXPECT_NO_THROW(inputDataset = reader->readData());
    EXPECT_EQ(inputDataset->columnNames, std::vector<std::string>({"NAMEUKR", "Count", "Unit", "CENA"}));
    EXPECT_EQ(inputDataset->dataRows.at(0), std::vector<std::string>({"Ім'я", "2", "шт", "123,10"}));

    // 2. Process data
    auto processor = SageDocs::DataProcessorFactory::createDataProcessor(SageDocs::DocType::SIMPLE_TABLE);
    std::shared_ptr<SageDocs::Dataset> outputDataset;
    EXPECT_NO_THROW(outputDataset = processor->process(inputDataset));
    EXPECT_EQ(inputDataset->columnNames, std::vector<std::string>({"Name", "Count", "Unit", "Price"}));
    EXPECT_EQ(inputDataset->dataRows.at(0), std::vector<std::string>({"Ім'я", "2", "шт", "123,10"}));

    // 3. Write data
    auto writer = SageDocs::WriterFactory::createWriter(SageDocs::WriterFileType::CSV);
    writer->setFileName("output_testMinimalCsvWorkCycle.csv");
    EXPECT_NO_THROW(writer->writeData(outputDataset));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
