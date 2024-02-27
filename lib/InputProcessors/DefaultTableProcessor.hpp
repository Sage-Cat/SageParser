#pragma once

#include <unordered_map>

#include "ITableProcessor.hpp"

namespace SageParser
{
    namespace DefaultColumnNames
    {
        const auto NAME = "name";
        const auto COUNT = "count";
        const auto UNIT = "unit";
        const auto PRICE = "price";
    }

    /**
     * @brief Process Table to have standard columns
     */
    class DefaultTableProcessor : public ITableProcessor
    {
    public:
        explicit DefaultTableProcessor() = default;

        /**
         * @brief Convert all table columns to have standard names
         *
         * @exception std::invalid_argument if table has column with name not specified in columnNameAliasses
         */
        std::shared_ptr<Table> process(const std::shared_ptr<Table> &table) override;
    };
}