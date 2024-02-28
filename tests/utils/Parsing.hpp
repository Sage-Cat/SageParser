#pragma once

#include <vector>
#include <sstream>

namespace SageParserTest
{
    std::vector<std::string> parseCsvLine(const std::string &line)
    {
        std::vector<std::string> values;
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ','))
        {
            values.push_back(cell);
        }

        return values;
    }
}