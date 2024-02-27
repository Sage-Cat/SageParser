project(SageParserLib)

# third party
find_package(rapidcsv REQUIRED)
find_package(pugixml REQUIRED)

set(LIB_SOURCES
    ${LIB_SOURCES_DIR}/InputProcessors/DefaultTableProcessor.cpp

    ${LIB_SOURCES_DIR}/Readers/CsvReader.cpp
    # ${LIB_SOURCES_DIR}/Readers/XmlReader.cpp

    ${LIB_SOURCES_DIR}/Writers/CsvWriter.cpp
    # ${LIB_SOURCES_DIR}/Writers/XmlWriter.cpp
)

add_library(SageParserLib ${LIB_SOURCES})

target_include_directories(SageParserLib PUBLIC ${LIB_SOURCES_DIR})

target_link_libraries(SageParserLib PRIVATE rapidcsv::rapidcsv pugixml::pugixml)
