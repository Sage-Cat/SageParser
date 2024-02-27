#pragma once

#include <filesystem>
#include <memory>

#include "DataTable.hpp"

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
         * @brief Writes data to the file from the provided DataTable representation.
         * @exception std::runtime_error if can't find or open file
         */
        virtual void write(const std::shared_ptr<DataTable> &dataTable) = 0;

    protected:
        std::filesystem::path filePath_;
    };

} // namespace SageParser
