#include "WriterFactory.hpp"

#include "Writers/CsvWriter.hpp"
#include "Writers/XmlWriter.hpp"

namespace SageParser
{
    std::unique_ptr<IWriter> WriterFactory::createWriter(WriterFileType type)
    {
        switch (type)
        {
        case WriterFileType::CSV:
            return std::make_unique<CsvWriter>();
        case WriterFileType::XML:
            return std::make_unique<XmlWriter>();
        default:
            throw std::invalid_argument("Unknown FileType provided");
        }
    }
}