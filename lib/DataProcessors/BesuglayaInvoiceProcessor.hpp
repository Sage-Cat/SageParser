#pragma once

#include "SimpleTableProcessor.hpp"

namespace SageDocs
{
    class BesuglayaInvoiceProcessor : public SimpleTableProcessor
    {
    public:
        explicit BesuglayaInvoiceProcessor() = default;

        std::shared_ptr<Dataset> process(const std::shared_ptr<Dataset> &dataset) override;
    };
}