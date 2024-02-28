#include "Table.hpp"
#include <algorithm>
#include <utility>

namespace SageParser
{

    Column &Table::operator[](const ColumnName &columnName)
    {
        auto [iter, inserted] = data_.try_emplace(columnName);
        if (inserted)
        {
            order_.push_back(columnName);
        }
        return iter->second;
    }

    std::unordered_map<ColumnName, Column> &Table::data()
    {
        return data_;
    }

    std::vector<ColumnName> Table::columnNames() const
    {
        std::vector<ColumnName> names;
        for (const auto &[key, _] : data_)
        {
            names.push_back(key);
        }
        return names;
    }

    void Table::renameColumn(const ColumnName &oldName, const ColumnName &newName)
    {
        if (oldName == newName)
            return;

        auto it = data_.find(oldName);
        if (it == data_.end())
            throw std::invalid_argument("renameColumn error: Column name '" + oldName + "' does not exist.");

        data_[newName] = std::move(it->second);
        data_.erase(it);
        std::ranges::replace(order_, oldName, newName);
    }

    const std::vector<ColumnName> &Table::getOrder() const
    {
        return order_;
    }

    bool Table::empty() const
    {
        return data_.empty();
    }

    bool Table::erase(const ColumnName &columnName)
    {
        auto it = data_.find(columnName);
        if (it != data_.end())
        {
            data_.erase(it);
            auto orderIt = std::remove(order_.begin(), order_.end(), columnName);
            order_.erase(orderIt, order_.end());
            return true;
        }
        return false;
    }

} // namespace SageParser
