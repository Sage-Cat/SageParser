#include "Table.hpp"
#include <algorithm>

namespace SageParser
{

    std::string &Table::at(int row, int column)
    {
        ensureRowExists(row);
        ensureColumnExists(column);
        return data_[row][column];
    }

    std::string &Table::at(int row, const std::string &columnName)
    {
        int columnIndex = getColumnIndex(columnName);
        return at(row, columnIndex);
    }

    void Table::addRow(const std::map<std::string, std::string> &rowData)
    {
        std::vector<std::string> newRow(indexesColumnNames_.size(), "");
        for (const auto &[columnName, value] : rowData)
        {
            int columnIndex = getColumnIndex(columnName);
            newRow[columnIndex] = value;
        }
        data_.push_back(std::move(newRow));
    }

    void Table::addRow(const std::map<int, std::string> &rowData)
    {
        std::vector<std::string> newRow(indexesColumnNames_.size(), "");
        for (const auto &[columnIndex, value] : rowData)
        {
            ensureColumnExists(columnIndex);
            newRow[columnIndex] = value;
        }
        data_.push_back(std::move(newRow));
    }

    void Table::addColumn(const std::string &columnName)
    {
        updateColumnMappings(columnName);
        for (auto &row : data_)
        {
            row.push_back("");
        }
    }

    std::map<int, std::string> Table::columnNamesMap() const
    {
        return indexesColumnNames_;
    }

    void Table::renameColumn(int columnIndex, const std::string &newName)
    {
        if (indexesColumnNames_.find(columnIndex) != indexesColumnNames_.end())
        {
            columnNameIndexes_.erase(indexesColumnNames_[columnIndex]);
            indexesColumnNames_[columnIndex] = newName;
            columnNameIndexes_[newName] = columnIndex;
        }
    }

    void Table::reserve(size_t rows, size_t columns)
    {
        data_.reserve(rows);
        for (auto &row : data_)
        {
            row.reserve(columns);
        }
        while (data_.size() < rows)
        {
            data_.emplace_back(columns, "");
        }
    }

    size_t Table::rowCount() const
    {
        return data_.size();
    }

    size_t Table::columnCount() const
    {
        return indexesColumnNames_.size();
    }

    void Table::eraseColumn(int columnIndex)
    {
        // Check if column exists
        if (!indexesColumnNames_.contains(columnIndex))
        {
            throw std::out_of_range("Column index out of range for erase");
        }

        // Erase column from each row
        for (auto &row : data_)
        {
            if (columnIndex < row.size())
            {
                row.erase(row.begin() + columnIndex);
            }
        }

        // Remove column from index mappings
        std::string erasedColumnName = indexesColumnNames_[columnIndex];
        indexesColumnNames_.erase(columnIndex);
        columnNameIndexes_.erase(erasedColumnName);

        // Adjust the mapping for columns that come after the erased one
        std::map<int, std::string> newColumnIndexes;
        std::map<std::string, int> newColumnNameIndexes;
        int newIndex = 0;
        for (const auto &[index, name] : indexesColumnNames_)
        {
            if (index > columnIndex)
            {
                newColumnIndexes[newIndex] = name;
                newColumnNameIndexes[name] = newIndex;
            }
            else
            {
                newColumnIndexes[index] = name;
                newColumnNameIndexes[name] = index;
            }
            newIndex++;
        }

        indexesColumnNames_ = std::move(newColumnIndexes);
        columnNameIndexes_ = std::move(newColumnNameIndexes);
    }

    void Table::ensureColumnExists(int columnIndex)
    {
        if (columnIndex >= static_cast<int>(data_.empty() ? 0 : data_[0].size()))
        {
            throw std::out_of_range("Column index out of range");
        }
    }

    void Table::ensureRowExists(int rowIndex)
    {
        if (rowIndex >= static_cast<int>(data_.size()))
        {
            throw std::out_of_range("Row index out of range");
        }
    }

    int Table::getColumnIndex(const std::string &columnName) const
    {
        auto it = columnNameIndexes_.find(columnName);
        if (it != columnNameIndexes_.end())
            return it->second;
        else
            return -1;
    }

    void Table::updateColumnMappings(const std::string &columnName)
    {
        if (columnNameIndexes_.find(columnName) == columnNameIndexes_.end())
        {
            int newIndex = indexesColumnNames_.size();
            indexesColumnNames_[newIndex] = columnName;
            columnNameIndexes_[columnName] = newIndex;
        }
    }

} // namespace SageParser
