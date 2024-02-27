#pragma once

#include <filesystem>
#include <memory>

#include "Table.hpp"

namespace SageParser
{
    /**
     * @brief Interface for classes that write data to various formats like CSV, JSON, XML, and XLSX.
     */
    class IWriter
    {
    public:
        explicit IWriter(const std::filesystem::path &new_path) : filePath_(new_path) {}
        virtual ~IWriter() = default;

        /**
         * @brief Writes data to the file from the provided Table representation.
         * @exception std::runtime_error if can't find or open file for writing
         */
        virtual void write(const std::shared_ptr<Table> &Table) = 0;

    protected:
        std::filesystem::path filePath_;
    };

} // namespace SageParser
