#pragma once

#include "SimpleTableProcessor.hpp"

namespace SageParser
{
    class OdooProductsProcessor : public SimpleTableProcessor
    {
    public:
        explicit OdooProductsProcessor() = default;

        std::shared_ptr<Table> process(const std::shared_ptr<Table> &Table) override;
    };
}