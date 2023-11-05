project(SageDocsLib)

# third party
find_package(csvmonkey REQUIRED)
find_package(pugixml REQUIRED)
find_package(xlnt REQUIRED)

set(LIB_SOURCES
    ${LIB_SOURCES_DIR}/DataProcessorFactory.cpp
    ${LIB_SOURCES_DIR}/ReaderFactory.cpp
    ${LIB_SOURCES_DIR}/WriterFactory.cpp
    ${LIB_SOURCES_DIR}/DataProcessors/SimpleDataProcessor.cpp
)

add_library(SageDocsLib ${LIB_SOURCES})

target_include_directories(SageDocsLib PUBLIC ${LIB_SOURCES_DIR})

target_link_libraries(SageDocsLib PRIVATE csvmonkey::csvmonkey pugixml::pugixml xlnt::xlnt)
