#include <gtest/gtest.h>

#include "DataProcessorFactory.cpp"
#include "DataProcessors/SimpleDataProcessor.cpp"

TEST(DataProcessorFactoryTest, ProperObjectIsCreated)
{
    auto processor = SageDocs::DataProcessorFactory::createDataProcessor(SageDocs::DocType::SIMPLE_TABLE);
    ASSERT_NE(nullptr, processor);
}

TEST(DataProcessorFactoryTest, CorrectDerivedObjectIsCreated)
{
    auto processor = SageDocs::DataProcessorFactory::createDataProcessor(SageDocs::DocType::SIMPLE_TABLE);
    EXPECT_EQ(typeid(SageDocs::SimpleDataProcessor), typeid(*processor));
}

// Main function that runs the tests when you execute the program
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
