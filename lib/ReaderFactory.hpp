#pragma once

#include "IReader.hpp"

namespace SageParser
{

    class ReaderFactory
    {
    public:
        ReaderFactory() = delete;
        ~ReaderFactory() = delete;

        static std::unique_ptr<IReader> createReader(ReaderFileType type);
    };
}