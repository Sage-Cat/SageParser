#include "WriterFactory.hpp"

#include "Writers/CsvWriter.hpp"

#include "Types.hpp"

namespace SageDocs
{
    std::unique_ptr<IWriter> WriterFactory::createWriter(WriterFileType type)
    {
        switch (type)
        {
        case WriterFileType::CSV:
            return std::make_unique<CsvWriter>();
        default:
            throw std::invalid_argument("Unknown FileType provided");
        }
    }
}