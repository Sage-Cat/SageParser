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
            {"NAIMUKR", Default::ColumnNames::NAME},
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
            {"BAZED", Default::ColumnNames::UNIT},

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

    std::shared_ptr<SageParser::Table> DefaultTableProcessor::process(const std::shared_ptr<SageParser::Table> &table)
    {
        auto new_table = std::make_shared<SageParser::Table>(*table);

        // Translate columns to default and remove unrecognized columns
        {
            auto columnNamesMap = new_table->columnNamesMap();

            // Prepare operations
            std::vector<std::pair<int, std::string>> renameOperations;
            std::vector<int> eraseOperations;
            for (const auto &[index, columnName] : columnNamesMap)
            {
                if (auto it = columnNamesAliases_.find(columnName); it != columnNamesAliases_.end())
                {
                    if (columnName != it->second)
                        renameOperations.emplace_back(index, it->second);
                }
                else
                {
                    eraseOperations.push_back(index);
                }
            }

            // Apply rename operations
            for (const auto &[index, newName] : renameOperations)
                new_table->renameColumn(index, newName);

            // Apply erase operations
            std::ranges::sort(eraseOperations, std::greater<>());
            for (int index : eraseOperations)
                new_table->eraseColumn(index);
        }

        // Translate units to default values, skip unrecognized
        if (int unitColumnIndex = new_table->getColumnIndex(Default::ColumnNames::UNIT.data()); unitColumnIndex != -1)
        {
            size_t numRows = new_table->rowCount(); // Assumes rowCount method is implemented to get the number of rows
            for (size_t row = 0; row < numRows; ++row)
            {
                std::string &unit = new_table->at(row, unitColumnIndex);
                if (auto aliasIt = unitAliases_.find(unit); aliasIt != unitAliases_.end())
                {
                    unit = aliasIt->second;
                }
            }
        }

        return new_table;
    }
}
