#include "CsvWriter.hpp"
#include <fstream>
#include <stdexcept>
#include <ranges>

namespace SageParser
{
    void CsvWriter::write(const std::shared_ptr<Table> &table)
    {
        if (filePath_.empty())
        {
            throw std::invalid_argument("File path is empty");
        }

        std::ofstream file(filePath_, std::ios::out | std::ios::trunc);
        if (!file.is_open())
        {
            throw std::runtime_error("Could not open file for writing at " + filePath_.string());
        }

        if (table->empty())
        {
            return;
        }

        // Utilize ranges to simplify loop operations
        const auto &columnNames = table->columnNames();
        bool isFirstColumn = true;
        for (const auto &columnName : columnNames)
        {
            if (!isFirstColumn)
                file << m_delimiter;
            if (m_useQuotes)
                file << '"' << columnName << '"';
            else
                file << columnName;
            isFirstColumn = false;
        }
        file << '\n';

        size_t numRows = table->begin()->second.size();

        for (size_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
        {
            isFirstColumn = true;
            for (const auto &[columnName, columnData] : *table)
            {
                if (!isFirstColumn)
                    file << m_delimiter;
                if (rowIndex < columnData.size())
                {
                    auto &value = columnData[rowIndex];
                    if (m_useQuotes)
                        file << '"' << value << '"';
                    else
                        file << value;
                }
                isFirstColumn = false;
            }
            file << '\n';
        }
    }
}
