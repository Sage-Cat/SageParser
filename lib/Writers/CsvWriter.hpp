#pragma once

#include "IWriter.hpp"

namespace SageDocs
{
    class CsvWriter : public IWriter
    {
    public:
        CsvWriter() = default;

        void setFileName(const std::string &name) override;
        void writeData(std::shared_ptr<Dataset> dataset) override;

    protected:
        std::string m_fileName{};
    };
}