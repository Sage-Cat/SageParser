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

        try
        {
            rapidcsv::Document doc(
                filePath_.string(), rapidcsv::LabelParams(0, -1),
                rapidcsv::SeparatorParams(m_delimiter, false,
                                          rapidcsv::sPlatformHasCR, true));

            auto table = std::make_shared<Table>();
            const std::vector<std::string> columnNames = doc.GetColumnNames();
            for (const auto &columnName : columnNames)
                table->addColumn(columnName);

            const std::size_t rowCount = doc.GetRowCount();
            for (std::size_t rowIndex = 0; rowIndex < rowCount; ++rowIndex)
            {
                std::map<std::string, std::string> rowData;
                for (const auto &columnName : columnNames)
                    rowData[columnName] = doc.GetCell<std::string>(columnName, rowIndex);
                table->addRow(rowData);
            }

            return table;
        }
        catch (const std::exception &error)
        {
            throw std::runtime_error("Failed to read CSV file " + filePath_.string()
                                     + ": " + error.what());
        }
    }

} // namespace SageParser
