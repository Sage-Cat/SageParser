#pragma once

#include <unordered_map>

#include "IDataProcessor.hpp"

namespace SageDocs
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

    class XmlProcessor : public IDataProcessor
    {
    public:
        explicit XmlProcessor();

        std::shared_ptr<Dataset> process(const std::shared_ptr<Dataset> &dataset) override;

    protected:
        std::unordered_map<std::string, std::string>
            m_columnNamesAliases{}, m_unitAliases{};
    };
}