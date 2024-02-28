#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <memory>
#include <ranges>

namespace SageParser
{

    using ColumnName = std::string;
    using Column = std::vector<std::string>;

    class Table
    {
    public:
        Column &operator[](const ColumnName &columnName);
        [[nodiscard]] std::unordered_map<ColumnName, Column> &data();
        [[nodiscard]] std::vector<ColumnName> columnNames() const;
        void renameColumn(const ColumnName &oldName, const ColumnName &newName);
        [[nodiscard]] const std::vector<ColumnName> &getOrder() const;
        [[nodiscard]] bool empty() const;
        bool erase(const ColumnName &columnName);

    private:
        std::unordered_map<ColumnName, Column> data_;
        std::vector<ColumnName> order_;
    };

} // namespace SageParser
