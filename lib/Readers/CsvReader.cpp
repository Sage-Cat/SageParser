#include "CsvReader.hpp"

namespace SageDocs
{
    void CsvReader::setFileName(const std::string &name)
    {
        this->m_fileName = name;
    }

    std::shared_ptr<Dataset> CsvReader::readData()
    {
        return std::shared_ptr<Dataset>();
    }
}