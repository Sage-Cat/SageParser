#pragma once

#include <concepts>
#include <string_view>
#include <unordered_map>

#include "AbstractProcessor.hpp"

namespace SageParser
{
    namespace DefaultColumnNames
    {
        inline constexpr std::string_view NAME = "name";
        inline constexpr std::string_view COUNT = "count";
        inline constexpr std::string_view UNIT = "unit";
        inline constexpr std::string_view PRICE = "price";
    }

    using alias_map = std::unordered_map<std::string, std::string>;

    /**
     * @brief Process Table to have standard columns
     */
    class DefaultTableProcessor : public AbstractProcessor
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