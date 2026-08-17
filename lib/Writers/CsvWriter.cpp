#include "CsvWriter.hpp"

#include <stdexcept>
#include <string_view>

namespace SageParser
{
    namespace
    {
        void writeField(std::ostream &output, std::string_view value,
                        char delimiter, bool alwaysQuote)
        {
            const bool quote = alwaysQuote
                || value.find(delimiter) != std::string_view::npos
                || value.find('"') != std::string_view::npos
                || value.find('\n') != std::string_view::npos
                || value.find('\r') != std::string_view::npos;

            if (!quote)
            {
                output << value;
                return;
            }

            output.put('"');
            for (const char character : value)
            {
                if (character == '"')
                    output.put('"');
                output.put(character);
            }
            output.put('"');
        }
    }

    void CsvWriter::write(const std::shared_ptr<Table> &table)
    {
        if (!table)
            throw std::invalid_argument("Table must not be null");
        if (filePath_.empty())
            throw std::invalid_argument("File path is empty");
        if (table->columnCount() == 0 && table->rowCount() != 0)
            throw std::invalid_argument("CSV output cannot represent rows without columns");

        std::ofstream file(filePath_, std::ios::out | std::ios::trunc);
        if (!file.is_open())
            throw std::runtime_error("Could not open file for writing at " + filePath_.string());

        const auto columnNames = table->columnNamesMap();
        if (!columnNames.empty())
        {
            for (auto iterator = columnNames.begin(); iterator != columnNames.end(); ++iterator)
            {
                if (iterator != columnNames.begin())
                    file.put(m_delimiter);
                writeField(file, iterator->second, m_delimiter, m_useQuotes);
            }
            file.put('\n');
        }

        for (std::size_t row = 0; row < table->rowCount(); ++row)
        {
            for (std::size_t column = 0; column < table->columnCount(); ++column)
            {
                if (column != 0)
                    file.put(m_delimiter);
                writeField(file, table->at(static_cast<int>(row), static_cast<int>(column)),
                           m_delimiter, m_useQuotes);
            }
            file.put('\n');
        }

        file.flush();
        if (!file)
            throw std::runtime_error("Failed while writing file at " + filePath_.string());
    }
} // namespace SageParser
