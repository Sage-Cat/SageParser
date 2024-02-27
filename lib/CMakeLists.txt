project(SageParserLib)

# third party
find_package(rapidcsv REQUIRED)
find_package(pugixml REQUIRED)

set(LIB_SOURCES
    ${LIB_SOURCES_DIR}/DataProcessorFactory.cpp
    ${LIB_SOURCES_DIR}/ReaderFactory.cpp
    ${LIB_SOURCES_DIR}/WriterFactory.cpp
    ${LIB_SOURCES_DIR}/Table.cpp

    ${LIB_SOURCES_DIR}/DataProcessors/SimpleTableProcessor.cpp
    ${LIB_SOURCES_DIR}/DataProcessors/BesuglayaInvoiceProcessor.cpp
    ${LIB_SOURCES_DIR}/DataProcessors/OdooProductsProcessor.cpp
    ${LIB_SOURCES_DIR}/DataProcessors/OmegaInvoiceProcessor.cpp
    ${LIB_SOURCES_DIR}/DataProcessors/OmegaPricelistProcessor.cpp

    ${LIB_SOURCES_DIR}/Readers/CsvReader.cpp
    ${LIB_SOURCES_DIR}/Readers/XmlReader.cpp

    ${LIB_SOURCES_DIR}/Writers/CsvWriter.cpp
    ${LIB_SOURCES_DIR}/Writers/XmlWriter.cpp
)

add_library(SageParserLib ${LIB_SOURCES})

target_include_directories(SageParserLib PUBLIC ${LIB_SOURCES_DIR})

target_link_libraries(SageParserLib PRIVATE rapidcsv::rapidcsv pugixml::pugixml)
