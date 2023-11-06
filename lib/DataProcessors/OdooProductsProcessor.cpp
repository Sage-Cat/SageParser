#include "OdooProductsProcessor.hpp"

namespace SageDocs
{
    std::shared_ptr<Dataset> OdooProductsProcessor::process(const std::shared_ptr<Dataset> &dataset)
    {
        // TODO: implementation
        return SimpleTableProcessor::process(dataset);
    }
}