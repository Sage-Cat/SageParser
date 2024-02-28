#pragma once

#include <concepts>
#include <string_view>
#include <unordered_map>

#include "IProcessor.hpp"

namespace SageParser
{
    namespace Default
    {

        namespace ColumnNames
        {
            inline constexpr std::string_view NAME = "name";
            inline constexpr std::string_view COUNT = "count";
            inline constexpr std::string_view UNIT = "unit";
            inline constexpr std::string_view PRICE = "price";
        }

        namespace Units
        {
            inline constexpr std::string_view PIECE = "шт.";
            inline constexpr std::string_view BUHT = "бхт.";
            inline constexpr std::string_view CANISTER = "Канистра";
            inline constexpr std::string_view BARREL = "Бочка";
            inline constexpr std::string_view BOX = "Кор.";
            inline constexpr std::string_view SET = "компл.";
        }
    }

    using alias_map = std::unordered_map<std::string, std::string>;

    /**
     * @brief Process Table to have standard columns
     */
    class DefaultTableProcessor : public IProcessor
    {
    public:
        explicit DefaultTableProcessor();
        ~DefaultTableProcessor() = default;

        /**
         * @brief Convert all Table columns to have standard names
         * @attention columnNames that was not recognized is removed
         */
        std::shared_ptr<Table> process(const std::shared_ptr<Table> &table) override;

    protected:
        alias_map columnNamesAliases_, unitAliases_;
    };
}