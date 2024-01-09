#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <optional>
#include <memory>

namespace SageDocs
{
    struct Dataset
    {
        using Row = std::vector<std::string>;

        std::vector<std::string> columnNames;
        std::vector<Row> dataRows;

        std::optional<size_t> getColumnIndex(const std::string &name) const;
    };

    // FUNCTIONS to work with datasets
    std::shared_ptr<Dataset> updateDataset(std::shared_ptr<Dataset> old_dataset, std::shared_ptr<Dataset> new_dataset, size_t columnIndex);
}
