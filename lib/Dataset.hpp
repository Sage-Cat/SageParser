#pragma once

#include <string>
#include <vector>

namespace DocsParser
{
    struct Dataset
    {
        std::vector<std::string> columnNames;
        std::vector<std::vector<std::string>> dataRows; // Assuming Rows is a vector of strings
    };
}