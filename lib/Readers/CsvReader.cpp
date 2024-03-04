#include "CsvReader.hpp"
#include <filesystem>
#include <stdexcept>
#include <rapidcsv.h>

namespace SageParser {

    std::shared_ptr<Table> CsvReader::read()
    {
        if (filePath_.empty())
        {
            throw std::runtime_error("File path is empty");
        }

        if (!std::filesystem::exists(filePath_) || !std::filesystem::is_regular_file(filePath_))
        {
            throw std::runtime_error("Invalid file path provided.");
        }

        rapidcsv::Document doc(filePath_.string(), rapidcsv::LabelParams(0, -1), rapidcsv::SeparatorParams(m_delimiter));

        auto table = std::make_shared<Table>();

        // Get column names and add them to the table
        std::vector<std::string> columnNames = doc.GetColumnNames();
        for (const auto &columnName : columnNames)
        {
            table->addColumn(columnName);
        }

        size_t rowCount = doc.GetRowCount();

        // Fill table with rows
        for (size_t rowIdx = 0; rowIdx < rowCount; ++rowIdx)
        {
            std::map<std::string, std::string> rowData;
            for (const auto &columnName : columnNames)
            {
                std::string cellValue = doc.GetCell<std::string>(columnName, rowIdx);
                rowData[columnName] = cellValue;
            }
            table->addRow(rowData);
        }

        return table;
    }

} // namespace SageParser
