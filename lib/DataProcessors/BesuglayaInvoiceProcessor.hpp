#pragma once

#include "SimpleTableProcessor.hpp"

namespace SageParser
{
    class BesuglayaInvoiceProcessor : public SimpleTableProcessor
    {
    public:
        explicit BesuglayaInvoiceProcessor() = default;

        std::shared_ptr<Table> process(const std::shared_ptr<Table> &Table) override;
    };
}