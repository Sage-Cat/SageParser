#pragma once

#include "SimpleTableProcessor.hpp"

namespace SageParser
{
    class OmegaInvoiceProcessor : public SimpleTableProcessor
    {
    public:
        explicit OmegaInvoiceProcessor() = default;

        std::shared_ptr<Table> process(const std::shared_ptr<Table> &Table) override;
    };
}