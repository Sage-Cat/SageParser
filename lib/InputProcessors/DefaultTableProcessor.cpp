#include "DefaultTableProcessor.hpp"
#include <ranges>
#include <algorithm>

namespace SageParser
{
    namespace
    {
        constexpr auto COLUMN_NAMES_ALIASES = std::to_array({
            // name
            std::pair{DefaultColumnNames::NAME, DefaultColumnNames::NAME},
            {"NAME", DefaultColumnNames::NAME},
            {"NAMEUKR", DefaultColumnNames::NAME},
            {"Name", DefaultColumnNames::NAME},

            // count
            {DefaultColumnNames::COUNT, DefaultColumnNames::COUNT},
            {"Count", DefaultColumnNames::COUNT},
            {"COUNT", DefaultColumnNames::COUNT},
            {"AMOUNT", DefaultColumnNames::COUNT},
            {"Amount", DefaultColumnNames::COUNT},

            // unit
            {DefaultColumnNames::UNIT, DefaultColumnNames::UNIT},
            {"UNIT", DefaultColumnNames::UNIT},
            {"Unit", DefaultColumnNames::UNIT},
            {"uom_id", DefaultColumnNames::UNIT},

            // price
            {DefaultColumnNames::PRICE, DefaultColumnNames::PRICE},
            {"PRICE", DefaultColumnNames::PRICE},
            {"CENA", DefaultColumnNames::PRICE},
            {"MINCENA", DefaultColumnNames::PRICE},
        });

        constexpr auto UNIT_ALIASES = std::to_array({
            // шт.
            std::pair{"шт.", "шт."},
            {"шт", "шт."},
            {"штук", "шт."},
            {"Шт", "шт."},

            // бхт.
            {"бхт.", "бхт."},
            {"бухт", "бхт."},

            // Канистра
            {"Канистра", "Канистра"},
            {"канистр", "Канистра"},
            {"каністр", "Канистра"},

            // Бочка
            {"Бочка", "Бочка"},
            {"бочк", "Бочка"},

            // Кор.
            {"Кор.", "Кор."},
            {"кор", "Кор."},

            // компл
            {"компл", "компл"},
            {"мотор.компл", "компл"},
        });
    }

    DefaultTableProcessor::DefaultTableProcessor()
    {
        columnNamesAliases_ = alias_map(COLUMN_NAMES_ALIASES.begin(), COLUMN_NAMES_ALIASES.end());
        unitAliases_ = alias_map(UNIT_ALIASES.begin(), UNIT_ALIASES.end());
    }

    std::shared_ptr<Table> DefaultTableProcessor::process(const std::shared_ptr<Table> &table)
    {
        auto new_table = std::make_shared<Table>(*table);

        // Rename columnNames with default names. Remove columns that is not known
        for (const auto &columnName : new_table->columnNames())
        {
            if (auto it = columnNamesAliases_.find(columnName); it != columnNamesAliases_.end())
            {
                if (columnName != it->second)
                    new_table->renameColumn(columnName, it->second);
            }
            else
            {
                new_table->erase(columnName);
            }
        }

        // Rename unit values with default names. Skip units that is not known
        if (auto it = new_table->find(DefaultColumnNames::UNIT.data()); it != new_table->end())
        {
            auto &unitColumn = it->second;
            for (auto &unit : unitColumn)
                if (auto it = unitAliases_.find(unit); it != unitAliases_.end())
                    unit = it->second;
        }

        return new_table;
    }
}
