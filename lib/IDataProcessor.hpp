#pragma once

#include "Dataset.hpp"

namespace SageDocs
{
    enum class DocType : int
    {
        SIMPLE_TABLE = 0,
        BESUGLAYA_INVOICE,
        OMEGA_INVOICE,
        OMEGA_PRICELIST,
        ODOO_PRODUCTS
    };

    class IDataProcessor
    {
    public:
        virtual std::shared_ptr<Dataset> process(std::shared_ptr<Dataset> dataset) = 0;
    };
}