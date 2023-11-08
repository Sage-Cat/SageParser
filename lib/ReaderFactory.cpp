#include "ReaderFactory.hpp"

#include "Readers/CsvReader.hpp"

namespace SageDocs
{
    std::unique_ptr<IReader> ReaderFactory::createReader(ReaderFileType type)
    {
        switch (type)
        {
        case ReaderFileType::CSV:
            return std::make_unique<CsvReader>();
        default:
            throw std::invalid_argument("Unknown ReaderFileType provided");
        }
    }
}