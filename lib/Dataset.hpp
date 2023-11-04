#pragma once

#include <string>
#include <vector>

namespace SageDocs
{
    using RawData = std::string;

    struct Dataset
    {
        using Row = std::vector<std::string>;

        std::vector<std::string> columnNames;
        std::vector<Row> dataRows;
    };
}