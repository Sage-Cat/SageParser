#include "BesuglayaInvoiceProcessor.hpp"

namespace SageDocs
{
    std::shared_ptr<Dataset> BesuglayaInvoiceProcessor::process(const std::shared_ptr<Dataset> &dataset)
    {
        // TODO: implementation
        return SimpleTableProcessor::process(dataset);
    }
}