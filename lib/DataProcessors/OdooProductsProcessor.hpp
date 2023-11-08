#pragma once

#include "SimpleTableProcessor.hpp"

namespace SageDocs
{
    class OdooProductsProcessor : public SimpleTableProcessor
    {
    public:
        explicit OdooProductsProcessor() = default;

        std::shared_ptr<Dataset> process(const std::shared_ptr<Dataset> &dataset) override;
    };
}