#include "CsvReader.hpp"
#include <filesystem>
#include <stdexcept>

#include <rapidcsv.h>
namespace SageDocs
{
    void CsvReader::setFilePath(const std::filesystem::path &new_path)
    {
        if (!std::filesystem::exists(new_path))
            throw std::invalid_argument("File path does not exist.");

        if (!std::filesystem::is_regular_file(new_path))
            throw std::invalid_argument("File path pointing not to a file.");

        m_filePath = new_path;
    }

    void CsvReader::setDelimiter(char new_delimiter)
    {
        m_delimiter = new_delimiter;
    }

    std::shared_ptr<Dataset> CsvReader::readData()
    {
        if (m_filePath.empty())
            throw std::invalid_argument("m_filePath is empty");

        // Ensure the file exists
        if (!std::filesystem::exists(m_filePath))
            throw std::invalid_argument("File path provided does not exist.");

        // Create a RapidCSV Document
        rapidcsv::Document doc(m_filePath.string(), rapidcsv::LabelParams(0, -1), rapidcsv::SeparatorParams(m_delimiter));

        auto dataset = std::make_shared<SageDocs::Dataset>();

        // Set column names
        dataset->columnNames = doc.GetColumnNames();

        // Read data rows
        for (size_t i = 0; i < doc.GetRowCount(); ++i)
        {
            SageDocs::Dataset::Row row = doc.GetRow<std::string>(i);
            dataset->dataRows.push_back(row);
        }
        return dataset;
    }
}
