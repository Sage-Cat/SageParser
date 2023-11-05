#pragma once

#include "IDataProcessor.hpp"

namespace SageDocs
{
    // Does main column renaming (makes it standardised)
    class SimpleTableProcessor : public IDataProcessor
    {
    public:
        explicit SimpleTableProcessor() = default;

        std::shared_ptr<Dataset> process(std::shared_ptr<Dataset> dataset) override;
    };
}