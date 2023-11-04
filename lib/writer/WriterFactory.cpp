#include "WriterFactory.hpp"

namespace SageDocs
{
    std::unique_ptr<IWriter> WriterFactory::createWriter(FileType type)
    {
        switch (type)
        {
        // TODO
        // case FileType::CSV:
        // case FileType::XML:
        default:
            throw std::invalid_argument("Unknown FileType provided");
        }
    }
}