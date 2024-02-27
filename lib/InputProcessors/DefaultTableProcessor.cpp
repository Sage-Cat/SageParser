#include "DefaultTableProcessor.hpp"

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

    std::shared_ptr<Table> DefaultTableProcessor::process(const std::shared_ptr<Table> &table)
    {
        auto new_table = std::make_shared<Table>(*table);
        std::unordered_map<std::string, std::string> columnNamesAliasesMap;
        for (const auto &[key, value] : COLUMN_NAMES_ALIASES)
        {
            columnNamesAliasesMap.emplace(key, value);
        }

        std::unordered_map<std::string, std::string> unitAliasesMap;
        for (const auto &[key, value] : UNIT_ALIASES)
        {
            unitAliasesMap.emplace(key, value);
        }

        // Use ranges to filter and erase columns not in COLUMN_NAMES_ALIASES
        for (const auto &columnName : new_table->columnNames())
        {
            if (columnNamesAliasesMap.find(columnName) == columnNamesAliasesMap.end())
            {
                new_table->erase(columnName);
            }
            else
            {
                auto aliasIt = columnNamesAliasesMap.find(columnName);
                if (aliasIt != columnNamesAliasesMap.end() && aliasIt->first != aliasIt->second)
                {
                    new_table->renameColumn(columnName, aliasIt->second);
                }
            }
        }

        // Update unit column based on UNIT_ALIASES
        try
        {
            auto &unitColumn = (*new_table)[DefaultColumnNames::UNIT];
            for (auto &unit : unitColumn)
            {
                auto aliasIt = unitAliasesMap.find(unit);
                if (aliasIt != unitAliasesMap.end())
                {
                    unit = aliasIt->second;
                }
                else
                {
                    throw std::invalid_argument("Encountered unexpected unit value");
                }
            }
        }
        catch (const std::out_of_range &)
        {
            throw std::invalid_argument("DefaultTableProcessor::process | Encountered unexpected unit");
        }

        return new_table;
    }
}