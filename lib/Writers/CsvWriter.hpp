#pragma once

#include <fstream>
#include <memory>
#include <string>

#include "IWriter.hpp"
#include "Table.hpp"

namespace SageParser
{
    class CsvWriter : public IWriter
    {
    public:
        explicit CsvWriter(const std::filesystem::path &new_path, char delimiter = ',', bool useQuotes = true)
            : IWriter(new_path), m_delimiter(delimiter), m_useQuotes(useQuotes) {}

        void write(const std::shared_ptr<Table> &table) override;

    private:
        char m_delimiter{'.'};
        bool m_useQuotes{true};
    };
}
