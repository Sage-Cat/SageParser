#pragma once

#include <unordered_map>

#include "IDataProcessor.hpp"

namespace SageParser
{
    namespace DefaultColumnNames
    {
        const auto NAME = "name";
        const auto COUNT = "count";
        const auto UNIT = "unit";
        const auto PRICE = "price";
    }

    // Does main column renaming (makes it standardised)
    class SimpleTableProcessor : public IDataProcessor
    {
    public:
        explicit SimpleTableProcessor();

        std::shared_ptr<Table> process(const std::shared_ptr<Table> &Table) override;

    protected:
        std::unordered_map<std::string, std::string>
            m_columnNamesAliases{}, m_unitAliases{};
    };
}