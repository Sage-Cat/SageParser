#include "Dataset.hpp"

namespace SageDocs
{
    std::optional<size_t> Dataset::getColumnIndex(const std::string &name) const
    {
        auto it = std::find(columnNames.begin(), columnNames.end(), name);
        if (it != columnNames.end())
        {
            return static_cast<size_t>(std::distance(columnNames.begin(), it));
        }
        return std::nullopt;
    }

    void updateDataset(std::shared_ptr<Dataset> old_dataset, const std::shared_ptr<Dataset> &new_dataset, size_t columnIndex)
    {
        // Validate the columnIndex is within range for both datasets
        if (columnIndex >= old_dataset->columnNames.size() || columnIndex >= new_dataset->columnNames.size())
        {
            throw std::invalid_argument("Column index is out of range for one or both datasets.");
        }

        // Map to quickly find rows in new_dataset by the key column value
        std::unordered_map<std::string_view, const Dataset::Row *> new_data_lookup;
        for (const auto &row : new_dataset->dataRows)
        {
            if (columnIndex < row.size())
            {
                new_data_lookup.emplace(row[columnIndex], &row);
            }
        }

        // Mapping of column names in new_dataset to their indices
        std::unordered_map<std::string_view, size_t> column_indices;
        for (size_t i = 0; i < new_dataset->columnNames.size(); ++i)
        {
            column_indices[new_dataset->columnNames[i]] = i;
        }

        // Iterate over the old dataset and update rows that have a matching key in the new dataset
        for (auto &row : old_dataset->dataRows)
        {
            if (columnIndex < row.size())
            {
                std::string_view key = row[columnIndex];
                if (auto it = new_data_lookup.find(key); it != new_data_lookup.end())
                {
                    // Found a matching row, update specific columns
                    for (size_t i = 0; i < row.size(); ++i)
                    {
                        if (auto col_it = column_indices.find(old_dataset->columnNames[i]);
                            col_it != column_indices.end() && col_it->second < it->second->size())
                        {
                            // Update the value in old_dataset with the value from new_dataset
                            row[i] = (*it->second)[col_it->second];
                        }
                    }
                }
            }
        }
    }
}
