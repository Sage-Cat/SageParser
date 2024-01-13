#include "ReaderFactory.hpp"

#include "Readers/CsvReader.hpp"
#include "Readers/XmlReader.hpp"
<<<<<<< HEAD

#include "Types.hpp"
=======
>>>>>>> f5c8d94cf7b49f9de629cccceb11a561298ec9e0

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