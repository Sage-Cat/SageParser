#include "DataProcessorFactory.hpp"
#include "DataProcessors/DefaultTableProcessor.hpp"
#include "DataProcessors/OmegaPricelistProcessor.hpp"

namespace SageParser
{
    std::unique_ptr<ITableProcessor> DataProcessorFactory::createDataProcessor(DocType type)
    {
        switch (type)
        {
        case DocType::SIMPLE_TABLE:
            return std::make_unique<DefaultTableProcessor>();
        case DocType::OMEGA_XMLPRICELIST:
            return std::make_unique<XmlProcessor>();
        // case DocType::BESUGLAYA_INVOICE:
        default:
            throw std::invalid_argument("Unknown DocType provided");
        }

        return nullptr;
    }
}