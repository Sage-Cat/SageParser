#pragma once

#include <memory>

#include "IWriter.hpp"

namespace SageDocs
{
    enum class FileType : int
    {
        // uncomment when ready
        // CSV = 0,
        // XML
    };

    class WriterFactory
    {
    public:
        WriterFactory() = delete;
        ~WriterFactory() = delete;

        static std::unique_ptr<IWriter> createWriter(FileType type);
    };
}