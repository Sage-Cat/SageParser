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

        if (table->rowCount() == 0)
            return;

        // Write column headers
        auto columnNamesMap = table->columnNamesMap();
        for (auto it = columnNamesMap.begin(); it != columnNamesMap.end(); ++it)
        {
            if (it != columnNamesMap.begin())
            {
                file << m_delimiter;
            }
            file << (m_useQuotes ? "\"" : "") << it->second << (m_useQuotes ? "\"" : "");
        }
        file << '\n';

        // Write row data
        size_t numRows = table->rowCount();
        size_t numColumns = table->columnCount();
        for (size_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
        {
            for (size_t columnIndex = 0; columnIndex < numColumns; ++columnIndex)
            {
                if (columnIndex > 0)
                {
                    file << m_delimiter;
                }
                std::string cellData = table->at(rowIndex, columnIndex);
                file << (m_useQuotes ? "\"" : "") << cellData << (m_useQuotes ? "\"" : "");
            }
            file << '\n';
        }
    }

} // namespace SageParser
