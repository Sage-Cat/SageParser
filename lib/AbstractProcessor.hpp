#pragma once

#include <memory>

#include "Table.hpp"

namespace SageParser
{
    /**
     * @brief Stub processor class. It is used as a base class for all processors
     */
    class AbstractProcessor
    {
    public:
        AbstractProcessor() = default;
        virtual ~AbstractProcessor() = default;

        /**
         * @brief stub method
         * @return empty Table object
         */
        virtual std::shared_ptr<Table> process(const std::shared_ptr<Table> &Table) { return {}; };
    };
}