#pragma once

#include <memory>

#include "Table.hpp"

namespace SageParser
{
    class AbstractProcessor
    {
    public:
        virtual std::shared_ptr<Table> process(const std::shared_ptr<Table> &Table) = 0;
    };
}