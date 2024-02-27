#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

namespace SageParser
{
    using Column = std::vector<std::string>;
    using ColumnName = std::string;
    using Table = std::unordered_map<ColumnName, Column>;
}
