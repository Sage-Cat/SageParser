#include "Table.hpp"

#include <utility>

namespace SageParser
{
    std::string &Table::at(int row, int column)
    {
        ensureRowExists(row);
        ensureColumnExists(column);
        return data_[static_cast<std::size_t>(row)][static_cast<std::size_t>(column)];
    }

    std::string &Table::at(int row, const std::string &columnName)
    {
        return at(row, getColumnIndex(columnName));
    }

    const std::string &Table::at(int row, int column) const
    {
        ensureRowExists(row);
        ensureColumnExists(column);
        return data_[static_cast<std::size_t>(row)][static_cast<std::size_t>(column)];
    }

    const std::string &Table::at(int row, const std::string &columnName) const
    {
        return at(row, getColumnIndex(columnName));
    }

    void Table::addRow(const std::map<std::string, std::string> &rowData)
    {
        std::vector<std::string> newRow(columnCount());
        for (const auto &[columnName, value] : rowData)
        {
            const int columnIndex = getColumnIndex(columnName);
            ensureColumnExists(columnIndex);
            newRow[static_cast<std::size_t>(columnIndex)] = value;
        }
        data_.push_back(std::move(newRow));
    }

    void Table::addRow(const std::map<int, std::string> &rowData)
    {
        std::vector<std::string> newRow(columnCount());
        for (const auto &[columnIndex, value] : rowData)
        {
            ensureColumnExists(columnIndex);
            newRow[static_cast<std::size_t>(columnIndex)] = value;
        }
        data_.push_back(std::move(newRow));
    }

    void Table::addColumn(const std::string &columnName)
    {
        updateColumnMappings(columnName);
        for (auto &row : data_)
            row.emplace_back();
    }

    std::map<int, std::string> Table::columnNamesMap() const
    {
        return indexesColumnNames_;
    }

    void Table::renameColumn(int columnIndex, const std::string &newName)
    {
        ensureColumnExists(columnIndex);
        if (newName.empty())
            throw std::invalid_argument("Column name must not be empty");

        const std::string oldName = indexesColumnNames_.at(columnIndex);
        if (newName == oldName)
            return;
        if (columnNameIndexes_.contains(newName))
            throw std::invalid_argument("Duplicate column name: " + newName);

        columnNameIndexes_.erase(oldName);
        indexesColumnNames_.at(columnIndex) = newName;
        columnNameIndexes_[newName] = columnIndex;
    }

    void Table::reserve(std::size_t rows, std::size_t columns)
    {
        data_.reserve(rows);
        for (auto &row : data_)
            row.reserve(columns);
    }

    std::size_t Table::rowCount() const
    {
        return data_.size();
    }

    std::size_t Table::columnCount() const
    {
        return indexesColumnNames_.size();
    }

    void Table::eraseColumn(int columnIndex)
    {
        ensureColumnExists(columnIndex);

        std::vector<std::string> remainingNames;
        remainingNames.reserve(columnCount() - 1);
        for (const auto &[index, name] : indexesColumnNames_)
        {
            if (index != columnIndex)
                remainingNames.push_back(name);
        }

        for (auto &row : data_)
            row.erase(row.begin() + columnIndex);

        indexesColumnNames_.clear();
        columnNameIndexes_.clear();
        for (const std::string &name : remainingNames)
        {
            const int index = static_cast<int>(indexesColumnNames_.size());
            indexesColumnNames_[index] = name;
            columnNameIndexes_[name] = index;
        }
    }

    void Table::ensureColumnExists(int columnIndex) const
    {
        if (columnIndex < 0 || static_cast<std::size_t>(columnIndex) >= columnCount())
            throw std::out_of_range("Column index out of range");
    }

    void Table::ensureRowExists(int rowIndex) const
    {
        if (rowIndex < 0 || static_cast<std::size_t>(rowIndex) >= rowCount())
            throw std::out_of_range("Row index out of range");
    }

    int Table::getColumnIndex(const std::string &columnName) const
    {
        const auto it = columnNameIndexes_.find(columnName);
        return it == columnNameIndexes_.end() ? -1 : it->second;
    }

    void Table::updateColumnMappings(const std::string &columnName)
    {
        if (columnName.empty())
            throw std::invalid_argument("Column name must not be empty");
        if (columnNameIndexes_.contains(columnName))
            throw std::invalid_argument("Duplicate column name: " + columnName);

        const int newIndex = static_cast<int>(indexesColumnNames_.size());
        indexesColumnNames_[newIndex] = columnName;
        columnNameIndexes_[columnName] = newIndex;
    }
} // namespace SageParser
