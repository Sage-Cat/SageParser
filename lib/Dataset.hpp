#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <optional>

namespace SageDocs
{
    struct Dataset
    {
        using Row = std::vector<std::string>;

        std::vector<std::string> columnNames;
        std::vector<Row> dataRows;

        std::optional<size_t> getColumnIndex(const std::string &name) const
        {
            auto it = std::find(columnNames.begin(), columnNames.end(), name);
            if (it != columnNames.end())
            {
                return static_cast<size_t>(std::distance(columnNames.begin(), it));
            }
            return std::nullopt;
        }
    };
}
