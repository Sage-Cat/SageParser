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

    class Table : public std::unordered_map<ColumnName, Column>
    {
    public:
        // Function to get all column names as a vector
        std::vector<ColumnName> columnNames() const
        {
            std::vector<ColumnName> names;
            for (const auto &[key, _] : *this)
            {
                names.push_back(key);
            }
            return names;
        }

        // Function to rename a column in a table
        void renameColumn(const ColumnName &oldName, const ColumnName &newName)
        {
            if (oldName == newName)
                return;

            auto it = find(oldName);
            if (it == end())
                throw std::invalid_argument("renameColumn error: Column name '" + oldName + "' does not exist.");

            (*this)[newName] = std::move(it->second);
            erase(it);
        }
    };

} // namespace SageParser
