#include "ReaderFactory.hpp"

#include "Readers/CsvReader.hpp"
#include "Readers/XmlReader.hpp"

#include "Types.hpp"

namespace SageDocs
{
    std::unique_ptr<IReader> ReaderFactory::createReader(ReaderFileType type)
    {
        switch (type)
        {
        case ReaderFileType::CSV:
            return std::make_unique<CsvReader>();
        case ReaderFileType::XML:
            return std::make_unique<XmlReader>();
        default:
            throw std::invalid_argument("Unknown ReaderFileType provided");
        }
    }
}