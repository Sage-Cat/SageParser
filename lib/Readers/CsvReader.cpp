#include "CsvReader.hpp"
#include <filesystem>
#include <stdexcept>
#include <rapidcsv.h>

namespace SageParser {

std::shared_ptr<DataTable> CsvReader::read() {
    if (filePath.empty()) {
        throw std::invalid_argument("File path is empty");
    }

    if (!std::filesystem::exists(filePath) || !std::filesystem::is_regular_file(filePath)) {
        throw std::invalid_argument("Invalid file path provided.");
    }

    rapidcsv::Document doc(filePath.string(), rapidcsv::LabelParams(0, -1), rapidcsv::SeparatorParams(m_delimiter));

    auto table = std::make_shared<DataTable>();

    std::vector<std::string> columnNames = doc.GetColumnNames();

    for (const auto& columnName : columnNames) {
        std::vector<std::string> columnData = doc.GetColumn<std::string>(columnName);
        (*table)[columnName] = std::move(columnData);
    }

    return table;
}

} // namespace SageParser
