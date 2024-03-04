#pragma once
#include <filesystem>
#include "IReader.hpp"
#include <unordered_set>
#include "pugixml.hpp"

namespace SageParser
{

    class XmlReader : public IReader
    {
    public:
        explicit XmlReader(const std::filesystem::path &filePath) : IReader(filePath) {}

        std::shared_ptr<Table> read() override;
    };

} // namespace SageParser