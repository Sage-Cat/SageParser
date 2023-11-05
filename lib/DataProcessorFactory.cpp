#include "DataProcessorFactory.hpp"

#include "DataProcessors/SimpleDataProcessor.hpp"

namespace SageDocs
{
    std::unique_ptr<IDataProcessor> DataProcessorFactory::createDataProcessor(DocType type)
    {
        switch (type)
        {
        case DocType::SIMPLE_TABLE:
            std::make_unique<SimpleDataProcessor>();
            break;
        // case DocType::BESUGLAYA_INVOICE:
        default:
            throw std::invalid_argument("Unknown DocType provided");
        }

        return nullptr;
    }
}