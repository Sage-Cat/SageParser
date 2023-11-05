#pragma once

#include "SimpleTableProcessor.hpp"

namespace SageDocs
{
    class OdooExportedProcessor : public SimpleTableProcessor
    {
    public:
        explicit OdooExportedProcessor() = default;

        std::shared_ptr<Dataset> process(std::shared_ptr<Dataset> dataset) override;
    };
}