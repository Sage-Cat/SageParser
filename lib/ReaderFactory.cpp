#include "ReaderFactory.hpp"

namespace SageDocs
{
    std::unique_ptr<IReader> ReaderFactory::createReader(ReaderFileType type)
    {
        switch (type)
        {
        // TODO
        // case ReaderFileType::CSV:
        // case ReaderFileType::XLSX:
        default:
            throw std::invalid_argument("Unknown ReaderFileType provided");
        }
    }
}