#pragma once

#include "Table.hpp"
#include "Types.hpp"

namespace SageParser
{
    class IDataProcessor
    {
    public:
        virtual std::shared_ptr<Table> process(const std::shared_ptr<Table> &Table) = 0;
    };
}