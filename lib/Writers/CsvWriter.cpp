#include "CsvWriter.hpp"
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
            return; // Early exit if table is empty
        }

        // Use getOrder to respect the column order
        const auto &columnOrder = table->getOrder();
        bool isFirstColumn = true;
        for (const auto &columnName : columnOrder)
        {
            file << (!isFirstColumn ? std::string{m_delimiter} : "") << (m_useQuotes ? "\"" : "") << columnName << (m_useQuotes ? "\"" : "");
            isFirstColumn = false;
        }
        file << '\n';

        // Assuming all columns have the same number of rows
        size_t numRows = table->data().begin()->second.size();
        for (size_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
        {
            isFirstColumn = true;
            for (const auto &columnName : columnOrder)
            {
                const auto &columnData = table->data().at(columnName);
                file << (!isFirstColumn ? std::string{m_delimiter} : "") << (m_useQuotes ? "\"" : "") << (rowIndex < columnData.size() ? columnData[rowIndex] : "") << (m_useQuotes ? "\"" : "");
                isFirstColumn = false;
            }
            file << '\n';
        }
    }

} // namespace SageParser