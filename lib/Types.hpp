#pragma once

namespace SageDocs
{
    enum class DocType : int
    {
        NONE = 0,
        SIMPLE_TABLE,
        BESUGLAYA_INVOICE,
        OMEGA_INVOICE,
        OMEGA_PRICELIST,
        ODOO_PRODUCTS
    };

    enum class ReaderFileType : int
    {
        NONE = 0,
        CSV,
        XLSX
    };

    enum class WriterFileType : int
    {
        NONE = 0,
        CSV,
        XLSX
    };
}