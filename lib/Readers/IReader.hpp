#pragma once

#include <filesystem>
#include <memory>

#include "Table.hpp"

namespace SageParser
{

    /**
     * @brief Interface for tabular file readers.
     */
    class IReader
    {
    public:
        explicit IReader(const std::filesystem::path &new_path) : filePath_(new_path) {}
        virtual ~IReader() = default;

        /**
         * @brief Reads data from the file and returns a representation in a Table.
         * @exception std::runtime_error if can't find or open file for reading
         */
        virtual std::shared_ptr<Table> read() = 0;

    protected:
        std::filesystem::path filePath_;
    };

} // namespace SageParser
