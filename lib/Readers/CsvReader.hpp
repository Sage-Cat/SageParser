#pragma once

#include "IReader.hpp"

namespace SageDocs
{
    class CsvReader : public IReader
    {
    public:
        CsvReader() = default;

        void setFileName(const std::string &name) override;
        std::shared_ptr<Dataset> readData() override;

    protected:
        std::string m_fileName{};
    };
}