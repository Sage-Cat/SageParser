#include "SimpleTableProcessor.hpp"

namespace SageParser
{
    SimpleTableProcessor::SimpleTableProcessor()
    {
        // COLUMN NAMES
        m_columnNamesAliases = {
            // name
            {"NAME", DefaultColumnNames::NAME},
            {"NAMEUKR", DefaultColumnNames::NAME},
            {"Name", DefaultColumnNames::NAME},

            // count
            {"Count", DefaultColumnNames::COUNT},
            {"COUNT", DefaultColumnNames::COUNT},
            {"AMOUNT", DefaultColumnNames::COUNT},
            {"Amount", DefaultColumnNames::COUNT},

            // unit
            {"UNIT", DefaultColumnNames::UNIT},
            {"Unit", DefaultColumnNames::UNIT},
            {"uom_id", DefaultColumnNames::UNIT},

            // price
            {"PRICE", DefaultColumnNames::PRICE},
            {"CENA", DefaultColumnNames::PRICE},
            {"MINCENA", DefaultColumnNames::PRICE},
        };

        // UNIT
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
            {"мотор.компл", "компл"},
        };
    }

    std::shared_ptr<Table> SimpleTableProcessor::process(const std::shared_ptr<Table> &Table)
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
        auto unitColumnIndexOpt = new_Table->getColumnIndex(DefaultColumnNames::UNIT);
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