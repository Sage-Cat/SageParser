#include "DataProcessorFactory.hpp"
#include "DataProcessors/DefaultDataTableProcessor.hpp"
#include "DataProcessors/OmegaPricelistProcessor.hpp"

namespace SageParser
{
    std::unique_ptr<IDataTableProcessor> DataProcessorFactory::createDataProcessor(DocType type)
    {
        switch (type)
        {
        case DocType::SIMPLE_DataTable:
            return std::make_unique<DefaultDataTableProcessor>();
        case DocType::OMEGA_XMLPRICELIST:
            return std::make_unique<XmlProcessor>();
        // case DocType::BESUGLAYA_INVOICE:
        default:
            throw std::invalid_argument("Unknown DocType provided");
        }

        return nullptr;
    }
}