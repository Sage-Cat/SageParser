#pragma once

#include <memory>

#include "Table.hpp"

namespace SageParser
{
    /**
     * @brief Interface for processors
     */
    class IProcessor
    {
    public:
        IProcessor() = default;
        virtual ~IProcessor() = default;

        /**
         * @brief Medhod to perform processing
         */
        virtual std::shared_ptr<Table> process(const std::shared_ptr<Table> &Table) = 0;
    };
}