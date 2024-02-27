#include "CsvWriter.hpp"
#include <fstream>
#include <stdexcept>

namespace SageParser
{
    void CsvWriter::write(const std::shared_ptr<DataTable> &dataTable)
    {
        if (filePath_.empty())
            throw std::invalid_argument("File path is empty");

        std::ofstream file(filePath_, std::ios::out | std::ios::trunc);
        if (!file.is_open())
            throw std::runtime_error("Could not open file for writing at " + filePath_.string());

        // Assuming the DataTable uses an unordered_map for storage
        if (dataTable->empty())
            return;

        // Write column headers
        bool isFirstColumn = true;
        for (const auto &columnName : dataTable->columnNames())
        {
            if (!isFirstColumn)
                file << ",";
            file << '"' << columnName << '"';
            isFirstColumn = false;
        }
        file << "\n";

        // Determine the number of rows by checking the size of the first column in the map
        size_t numRows = dataTable->begin()->second.size();

        // Write data rows
        for (size_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
        {
            isFirstColumn = true;
            for (const auto &[columnName, columnData] : *dataTable)
            {
                if (!isFirstColumn)
                    file << ",";
                // Ensure row exists for column
                if (rowIndex < columnData.size())
                {
                    file << '"' << columnData[rowIndex] << '"';
                }
                isFirstColumn = false;
            }
            file << "\n";
        }
    }
}
