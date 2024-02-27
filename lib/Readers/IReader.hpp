#pragma once

#include <filesystem>
#include <memory>

#include "DataTable.hpp"

namespace SageParser
{

    /**
     * @brief Interface for file readers, supporting various formats like CSV, JSON, XML, and XLSX.
     */
    class IReader
    {
    public:
        explicit IReader(const std::filesystem::path &new_path) : filePath(new_path) {}
        virtual ~IReader() = default;

        /**
         * @brief Reads data from the file and returns a representation in a DataTable.
         * @exception std::runtime_error if can't find or open file for reading
         */
        virtual std::shared_ptr<DataTable> read() = 0;

    protected:
        std::filesystem::path filePath;
    };

} // namespace SageParser
