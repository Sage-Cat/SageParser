#include "DataProcessorFactory.hpp"

namespace SageDocs
{
    std::unique_ptr<IDataProcessor> DataProcessorFactory::createDataProcessor(DocType type)
    {
        switch (type)
        {
        // TODO
        // case DocType::SIMPLE_TABLE:
        // case DocType::BESUGLAYA_INVOICE:
        default:
            throw std::invalid_argument("Unknown DocType provided");
        }
    }
}