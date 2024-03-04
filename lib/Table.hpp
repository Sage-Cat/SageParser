#pragma once

#include <string>
#include <vector>
#include <map>
#include <stdexcept>

namespace SageParser
{

    class Table
    {
    public:
        Table() = default;

        std::string &at(int row, int column);
        std::string &at(int row, const std::string &columnName);

        void addRow(const std::map<std::string, std::string> &rowData);
        void addRow(const std::map<int, std::string> &rowData);
        void addColumn(const std::string &columnName);

        [[nodiscard]] std::map<int, std::string> columnNamesMap() const;
        void renameColumn(int columnIndex, const std::string &newName);
        void eraseColumn(int columnIndex);

        void reserve(size_t rows, size_t columns);

        [[nodiscard]] size_t rowCount() const;
        [[nodiscard]] size_t columnCount() const;
        [[nodiscard]] int getColumnIndex(const std::string &columnName) const;

    private:
        void ensureColumnExists(int columnIndex);
        void ensureRowExists(int rowIndex);
        void updateColumnMappings(const std::string &columnName);

    private:
        std::vector<std::vector<std::string>> data_;
        std::map<int, std::string> indexesColumnNames_;
        std::map<std::string, int> columnNameIndexes_;
    };

} // namespace SageParser
