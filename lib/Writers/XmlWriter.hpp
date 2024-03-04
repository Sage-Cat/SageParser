#pragma once

#include "IWriter.hpp"

namespace SageParser
{
    class XmlWriter : public IWriter
    {
    public:
        explicit XmlWriter(const std::filesystem::path &filePath) : IWriter(filePath) {}

        void write(const std::shared_ptr<Table> &table) override;
    };
}