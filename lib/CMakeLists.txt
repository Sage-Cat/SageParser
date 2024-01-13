project(SageDocsLib)

# third party
find_package(rapidcsv REQUIRED)
find_package(pugixml REQUIRED)
<<<<<<< HEAD
# find_package(xlnt REQUIRED)
=======
find_package(xlnt REQUIRED)
>>>>>>> f5c8d94cf7b49f9de629cccceb11a561298ec9e0
# find_package(ICU REQUIRED)

set(LIB_SOURCES
    ${LIB_SOURCES_DIR}/DataProcessorFactory.cpp
    ${LIB_SOURCES_DIR}/ReaderFactory.cpp
    ${LIB_SOURCES_DIR}/WriterFactory.cpp
    ${LIB_SOURCES_DIR}/Dataset.cpp

    ${LIB_SOURCES_DIR}/DataProcessors/SimpleTableProcessor.cpp
    ${LIB_SOURCES_DIR}/DataProcessors/BesuglayaInvoiceProcessor.cpp
    ${LIB_SOURCES_DIR}/DataProcessors/OdooProductsProcessor.cpp
    ${LIB_SOURCES_DIR}/DataProcessors/OmegaInvoiceProcessor.cpp

    ${LIB_SOURCES_DIR}/Readers/CsvReader.cpp
    ${LIB_SOURCES_DIR}/Readers/XmlReader.cpp

    ${LIB_SOURCES_DIR}/Writers/CsvWriter.cpp
    ${LIB_SOURCES_DIR}/Writers/XmlWriter.cpp
)

add_library(SageDocsLib ${LIB_SOURCES})

target_include_directories(SageDocsLib PUBLIC ${LIB_SOURCES_DIR})

# target_link_libraries(SageDocsLib PRIVATE rapidcsv::rapidcsv icu::icu pugixml::pugixml xlnt::xlnt)
<<<<<<< HEAD
target_link_libraries(SageDocsLib PRIVATE rapidcsv::rapidcsv pugixml::pugixml)
# target_link_libraries(SageDocsLib PRIVATE rapidcsv::rapidcsv icu::icu pugixml::pugixml xlnt::xlnt)
=======
target_link_libraries(SageDocsLib PRIVATE rapidcsv::rapidcsv pugixml::pugixml xlnt::xlnt)
>>>>>>> f5c8d94cf7b49f9de629cccceb11a561298ec9e0
