#include "OmegaPricelistProcessor.hpp"
namespace SageParser
{

    XmlProcessor::XmlProcessor()
    {
        // column names
        m_columnNamesAliases = {
            // name
            // {"NAIM", DefaultColumn::NAME},
            {"NAIMUKR", DefaultColumn::NAME},
            // {"PRIM", DefaultColumn::NAME},

            // price //15
            {"CENAPART", DefaultColumn::PRICE},
            {"MINCENA", DefaultColumn::PRICE},
            //{"ROZNCENA", DefaultColumn::PRICE},

            // unit
            {"BAZED", DefaultColumn::UNIT},

            // id
            {"KART", DefaultColumn::ID},
            // {"KODKAT", DefaultColumn::ID},
            //{"KODTNVED", DefaultColumn::ID}

            // import
            {"IMPORT", DefaultColumn::IMPORT}

        };

        m_unitAliases = {
            // шт
            {"шт", "шт."},
            {"штук", "шт."},
            {"Шт", "шт."},

            // бхт
            {"бухт", "бхт."},

            // Канистра
            {"канистр", "Канистра"},
            {"каністр", "Канистра"},

            // Бочка
            {"бочк", "Бочка"},

            // Кор.
            {"кор", "Кор."},

            // компл
            {"мотор.компл", "компл"}};
    }
    std::shared_ptr<Table> XmlProcessor::process(const std::shared_ptr<Table> &Table)
    {
        auto new_Table = std::make_shared<Table>(*Table);

        // Process column names
        for (auto &column_name : new_Table->columnNames)
        {
            auto alias_it = m_columnNamesAliases.find(column_name);
            if (alias_it != m_columnNamesAliases.end())
            {
                column_name = alias_it->second;
            }
        }

        // Process unit names
        auto unitColumnIndexOpt = new_Table->getColumnIndex(DefaultColumn::UNIT);
        if (unitColumnIndexOpt)
        {
            size_t unitColumnIndex = unitColumnIndexOpt.value();
            for (auto &row : new_Table->dataRows)
            {
                auto unit_alias_it = m_unitAliases.find(row[unitColumnIndex]);
                if (unit_alias_it != m_unitAliases.end())
                {
                    row[unitColumnIndex] = unit_alias_it->second;
                }
            }
        }

        return new_Table;
    }
}