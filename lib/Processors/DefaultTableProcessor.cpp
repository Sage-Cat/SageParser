#include "DefaultTableProcessor.hpp"
#include <ranges>
#include <algorithm>

namespace SageParser
{
    namespace
    {
        constexpr auto COLUMN_NAMES_ALIASES = std::to_array({
            // name
            std::pair{Default::ColumnNames::NAME, Default::ColumnNames::NAME},
            {"NAME", Default::ColumnNames::NAME},
            {"NAMEUKR", Default::ColumnNames::NAME},
            {"Name", Default::ColumnNames::NAME},

            // count
            {Default::ColumnNames::COUNT, Default::ColumnNames::COUNT},
            {"Count", Default::ColumnNames::COUNT},
            {"COUNT", Default::ColumnNames::COUNT},
            {"AMOUNT", Default::ColumnNames::COUNT},
            {"Amount", Default::ColumnNames::COUNT},

            // unit
            {Default::ColumnNames::UNIT, Default::ColumnNames::UNIT},
            {"UNIT", Default::ColumnNames::UNIT},
            {"Unit", Default::ColumnNames::UNIT},
            {"uom_id", Default::ColumnNames::UNIT},

            // price
            {Default::ColumnNames::PRICE, Default::ColumnNames::PRICE},
            {"PRICE", Default::ColumnNames::PRICE},
            {"CENA", Default::ColumnNames::PRICE},
            {"MINCENA", Default::ColumnNames::PRICE},
        });

        constexpr auto UNIT_ALIASES = std::to_array({
            // шт.
            std::pair{Default::Units::PIECE, Default::Units::PIECE},
            {"шт", Default::Units::PIECE},
            {"штук", Default::Units::PIECE},
            {"Шт", Default::Units::PIECE},

            // бхт.
            {Default::Units::BUHT, Default::Units::BUHT},
            {"бухт", Default::Units::BUHT},

            // Канистра
            {Default::Units::CANISTER, Default::Units::CANISTER},
            {"канистр", Default::Units::CANISTER},
            {"каністр", Default::Units::CANISTER},

            // Бочка
            {Default::Units::BARREL, Default::Units::BARREL},
            {"бочк", Default::Units::BARREL},

            // Кор.
            {Default::Units::BOX, Default::Units::BOX},
            {"кор", Default::Units::BOX},

            // компл
            {Default::Units::SET, Default::Units::SET},
            {"мотор.компл", Default::Units::SET},
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
        auto &table_data = new_table->data();

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
        if (auto it = table_data.find(Default::ColumnNames::UNIT.data()); it != table_data.end())
        {
            auto &unitColumn = it->second;
            for (auto &unit : unitColumn)
                if (auto aliasIt = unitAliases_.find(unit); aliasIt != unitAliases_.end())
                    unit = aliasIt->second;
        }

        return new_table;
    }
}
