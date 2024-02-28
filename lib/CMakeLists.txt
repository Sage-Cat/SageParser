project(SageParserLib)

# third party
find_package(rapidcsv REQUIRED)
find_package(pugixml REQUIRED)

set(LIB_SOURCES
    ${LIB_SOURCES_DIR}/ParserBuilder.cpp
    ${LIB_SOURCES_DIR}/Table.cpp

    # Processors
    ${LIB_SOURCES_DIR}/Processors/DefaultTableProcessor.cpp

    # Readers
    ${LIB_SOURCES_DIR}/Readers/CsvReader.cpp
    # ${LIB_SOURCES_DIR}/Readers/XmlReader.cpp

    # Writers
    ${LIB_SOURCES_DIR}/Writers/CsvWriter.cpp
    # ${LIB_SOURCES_DIR}/Writers/XmlWriter.cpp
)

add_library(SageParserLib ${LIB_SOURCES})

target_include_directories(SageParserLib PUBLIC ${LIB_SOURCES_DIR})

target_link_libraries(SageParserLib PRIVATE rapidcsv::rapidcsv pugixml::pugixml)
