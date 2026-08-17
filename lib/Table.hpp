#pragma once

#include <cstddef>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace SageParser
{

    class Table
    {
    public:
        Table() = default;

        std::string &at(int row, int column);
        std::string &at(int row, const std::string &columnName);
        const std::string &at(int row, int column) const;
        const std::string &at(int row, const std::string &columnName) const;

        void addRow(const std::map<std::string, std::string> &rowData);
        void addRow(const std::map<int, std::string> &rowData);
        void addColumn(const std::string &columnName);

        [[nodiscard]] std::map<int, std::string> columnNamesMap() const;
        void renameColumn(int columnIndex, const std::string &newName);
        void eraseColumn(int columnIndex);

        void reserve(std::size_t rows, std::size_t columns);

        [[nodiscard]] std::size_t rowCount() const;
        [[nodiscard]] std::size_t columnCount() const;
        [[nodiscard]] int getColumnIndex(const std::string &columnName) const;

    private:
        void ensureColumnExists(int columnIndex) const;
        void ensureRowExists(int rowIndex) const;
        void updateColumnMappings(const std::string &columnName);

    private:
        std::vector<std::vector<std::string>> data_;
        std::map<int, std::string> indexesColumnNames_;
        std::map<std::string, int> columnNameIndexes_;
    };

} // namespace SageParser
