#include "DefaultDataTableProcessor.hpp"

#include <array>
#include <memory>

namespace SageParser
{
    inline constexpr auto COLUMN_NAMES_ALIASES = std::to_array<std::pair<std::string_view, std::string_view>>({
        // name
        {DefaultColumnNames::NAME, DefaultColumnNames::NAME},
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

    inline constexpr auto UNIT_ALIASES = std::to_array<std::pair<std::string_view, std::string_view>>({
        {"шт.", "шт."},
        {"шт", "шт."},
        {"штук", "шт."},
        {"Шт", "шт."},

        // бхт
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

    std::shared_ptr<DataTable> DefaultDataTableProcessor::process(const std::shared_ptr<DataTable> &dataTable)
    {
        auto new_DataTable = std::make_shared<DataTable>(*DataTable);

        // Process column names
        try
        {
            for (auto &column_name : new_DataTable->columnNames())
            {
                new_DataTable->renameColumn(column_name, COLUMN_NAMES_ALIASES.at(column_name));
            }
        }
        catch (const std::out_of_range &e)
        {
            throw std::invalid_argument("DefaultDataTableProcessor::process | Met unexpected column name");
        }

        try
        {
            auto &unitColumn = new_DataTable[DefaultColumnNames::UNIT];
            if (!unitColumn.empty())
                for (auto &unit : unitColumn)
                    unit = UNIT_ALIASES.at(unit);
        }
        catch (const std::out_of_range &e)
        {
            throw std::invalid_argument("DefaultDataTableProcessor::process | Met unexpected unit");
        }

        return new_DataTable;
    }
}