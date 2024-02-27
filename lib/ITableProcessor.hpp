#pragma once

#include <memory>

#include "DataTable.hpp"

namespace SageParser
{
    class IDataTableProcessor
    {
    public:
        virtual std::shared_ptr<DataTable> process(const std::shared_ptr<DataTable> &dataTable) = 0;
    };
}