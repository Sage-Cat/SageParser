#pragma once

#include "IWriter.hpp"

namespace SageParser
{
    class WriterFactory
    {
    public:
        WriterFactory() = delete;
        ~WriterFactory() = delete;

        static std::unique_ptr<IWriter> createWriter(WriterFileType type);
    };
}