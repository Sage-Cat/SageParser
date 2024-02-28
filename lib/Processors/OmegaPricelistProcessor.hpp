#pragma once

#include <unordered_map>

#include "IProcessor.hpp"

namespace SageParser
{
    namespace DefaultColumn
    {
        const auto NAME = "name";
        const auto COUNT = "count";
        const auto UNIT = "unit";
        const auto PRICE = "price";
        const auto ID = "id";
        const auto IMPORT = "import";
    }

    class XmlProcessor : public IProcessor
    {
    public:
        explicit XmlProcessor();

        std::shared_ptr<Table> process(const std::shared_ptr<Table> &Table) override;

    protected:
        std::unordered_map<std::string, std::string>
            m_columnNamesAliases{}, m_unitAliases{};
    };
}