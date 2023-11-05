#pragma once

#include "Dataset.hpp"

namespace SageDocs
{
    enum class WriterFileType : int
    {
        CSV = 0,
        XML
    };

    class IWriter
    {
    public:
        virtual void setFileName(const std::string &name) = 0;
        virtual void writeData(std::shared_ptr<Dataset> dataset) = 0;
    };
}