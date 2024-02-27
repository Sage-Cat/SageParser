#pragma once

#include "IWriter.hpp"

namespace SageParser
{
    class XmlWriter : public IWriter
    {
    public:
        XmlWriter() = default;

        void setFilePath(const std::filesystem::path &new_path) override;

        void write(const std::shared_ptr<Table> &Table) override;

    protected:
        std::filesystem::path m_filePath;
    };
}