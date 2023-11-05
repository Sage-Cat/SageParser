#pragma once

#include <memory>

#include "IWriter.hpp"

namespace SageDocs
{
    class WriterFactory
    {
    public:
        WriterFactory() = delete;
        ~WriterFactory() = delete;

        static std::unique_ptr<IWriter> createWriter(WriterFileType type);
    };
}