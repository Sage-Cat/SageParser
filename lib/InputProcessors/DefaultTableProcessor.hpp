#pragma once

#include <unordered_map>

#include "AbstractProcessor.hpp"

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
    class DefaultTableProcessor : public AbstractProcessor
    {
    public:
        explicit DefaultTableProcessor() = default;

        /**
         * @brief Convert all Table columns to have standard names
         * @attention columnNames that was not recognized is removed
         */
        std::shared_ptr<Table> process(const std::shared_ptr<Table> &table) override;
    };
}