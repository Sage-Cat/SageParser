#pragma once

#include <string>
#include <vector>
#include <memory>

namespace SageDocs
{
    struct Dataset
    {
        using Row = std::vector<std::string>;

        std::vector<std::string> columnNames;
        std::vector<Row> dataRows;
    };
}