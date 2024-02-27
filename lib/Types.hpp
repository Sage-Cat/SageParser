#pragma once

namespace SageParser
{
    enum class DocType : int
    {
        NONE = 0,
        SIMPLE_TABLE,
        BESUGLAYA_INVOICE,
        OMEGA_INVOICE,
        OMEGA_PRICELIST,
        ODOO_PRODUCTS,
        OMEGA_XMLPRICELIST
    };

    enum class ReaderFileType : int
    {
        NONE = 0,
        CSV,
        XLSX,
        XML
    };

    enum class WriterFileType : int
    {
        NONE = 0,
        CSV,
        XLSX,
        XML
    };
}