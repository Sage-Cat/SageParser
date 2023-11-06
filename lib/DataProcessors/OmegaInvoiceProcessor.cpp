#include "OmegaInvoiceProcessor.hpp"

namespace SageDocs
{
    std::shared_ptr<Dataset> OmegaInvoiceProcessor::process(const std::shared_ptr<Dataset> &dataset)
    {
        // TODO: implementation
        return SimpleTableProcessor::process(dataset);
    }
}