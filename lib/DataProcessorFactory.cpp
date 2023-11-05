#include "DataProcessorFactory.hpp"

#include "DataProcessors\SimpleTableProcessor.hpp"

namespace SageDocs
{
    std::unique_ptr<IDataProcessor> DataProcessorFactory::createDataProcessor(DocType type)
    {
        switch (type)
        {
        case DocType::SIMPLE_TABLE:
            return std::make_unique<SimpleTableProcessor>();
        // case DocType::BESUGLAYA_INVOICE:
        default:
            throw std::invalid_argument("Unknown DocType provided");
        }

        return nullptr;
    }
}