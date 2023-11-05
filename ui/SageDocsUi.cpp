#include "SageDocsUi.hpp"

#include <iostream>

#include "parser/DataProcessorFactory.hpp"
#include "reader/ReaderFactory.hpp"
#include "writer/WriterFactory.hpp"

void SageDocsUi::init()
{
    // FOR TESTING PURPOSE
    // TODO: remove
    try
    {
        auto DataProcessorFactory = SageDocs::DataProcessorFactory::createDataProcessor(SageDocs::DocType::SIMPLE_TABLE);
    }
    catch (const std::exception &ex)
    {
        std::cout << "Exception: " << ex.what() << std::endl;
    }
}