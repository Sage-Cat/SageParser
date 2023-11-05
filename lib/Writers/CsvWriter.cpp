#include "CsvWriter.hpp"

namespace SageDocs
{
    void CsvWriter::setFileName(const std::string &name)
    {
        this->m_fileName = name;
    }

    void CsvWriter::writeData(std::shared_ptr<Dataset> dataset)
    {
    }
}