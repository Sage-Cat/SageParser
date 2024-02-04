#include "XmlProcessor.hpp"

namespace SageDocs
{

    XmlProcessor::XmlProcessor()
    {
        // column names
        m_columnNamesAliases = {
            // name
            {"NAIM", DefaultColumn::NAME},
            {"NAIMUKR", DefaultColumn::NAME},
            {"PRIM", DefaultColumn::NAME},

            // price
            {"CENAPART", DefaultColumn::PRICE},
            {"MINCENA", DefaultColumn::PRICE},
            {"ROZNCENA", DefaultColumn::PRICE},

            // unit
            {"BAZED", DefaultColumn::UNIT},

            // id
            {"KART", DefaultColumn::ID},
            {"KODKAT", DefaultColumn::ID},
            {"KODTNVED", DefaultColumn::ID}

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
    std::shared_ptr<Dataset> XmlProcessor::process(const std::shared_ptr<Dataset> &dataset)
    {
        auto new_dataset = std::make_shared<Dataset>(*dataset);

        // Process column names
        for (auto &column_name : new_dataset->columnNames)
        {
            auto alias_it = m_columnNamesAliases.find(column_name);
            if (alias_it != m_columnNamesAliases.end())
            {
                column_name = alias_it->second;
            }
        }

        // Process unit names
        auto unitColumnIndexOpt = new_dataset->getColumnIndex(DefaultColumn::UNIT);
        if (unitColumnIndexOpt)
        {
            size_t unitColumnIndex = unitColumnIndexOpt.value();
            for (auto &row : new_dataset->dataRows)
            {
                auto unit_alias_it = m_unitAliases.find(row[unitColumnIndex]);
                if (unit_alias_it != m_unitAliases.end())
                {
                    row[unitColumnIndex] = unit_alias_it->second;
                }
            }
        }

        return new_dataset;
    }
}