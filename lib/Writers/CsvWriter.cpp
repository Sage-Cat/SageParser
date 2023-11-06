#include "CsvWriter.hpp"

#include <fstream>
#include <sstream>
#include <iomanip>

namespace SageDocs
{
    void CsvWriter::setFilePath(const std::filesystem::path &new_path)
    {
        if (!std::filesystem::exists(new_path.parent_path()))
            throw std::invalid_argument("Directory path does not exist.");

        if (std::filesystem::is_directory(new_path))
            throw std::invalid_argument("File path is a directory.");

        m_filePath = new_path;
    }

    void CsvWriter::writeData(const std::shared_ptr<Dataset> &dataset)
    {
        if (m_filePath.empty())
            throw std::invalid_argument("m_filePath is empty");

        std::ofstream file(m_filePath, std::ios::out | std::ios::trunc);
        if (!file.is_open())
            throw std::invalid_argument("Could not open m_filePath for writing");

        // Helper lambda to quote and escape a field
        auto quote = [](const std::string &field)
        {
            std::ostringstream ss;
            ss << '"' << field << '"';
            return ss.str();
        };

        // Write column names
        bool firstColumn = true;
        for (const auto &columnName : dataset->columnNames)
        {
            if (!firstColumn)
                file << ",";
            file << quote(columnName);
            firstColumn = false;
        }
        file << "\n";

        // Write data rows
        for (const auto &row : dataset->dataRows)
        {
            firstColumn = true;
            for (const auto &cell : row)
            {
                if (!firstColumn)
                    file << ",";
                file << quote(cell);
                firstColumn = false;
            }
            file << "\n";
        }
    }
}
