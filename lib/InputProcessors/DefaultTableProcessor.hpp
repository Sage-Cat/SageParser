#pragma once

#include <unordered_map>

#include "IDataTableProcessor.hpp"

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
     * @brief Process DataTable to have standard columns
     */
    class DefaultDataTableProcessor : public IDataTableProcessor
    {
    public:
        explicit DefaultDataTableProcessor() = default;

        /**
         * @brief Convert all DataTable columns to have standard names
         * @exception std::invalid_argument if DataTable has column with name not specified in columnNameAliasses
         */
        std::shared_ptr<DataTable> process(const std::shared_ptr<DataTable> &dataTable) override;
    };
}