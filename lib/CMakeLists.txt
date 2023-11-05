project(SageDocsLib)

# third party
find_package(csvmonkey REQUIRED)
find_package(pugixml REQUIRED)
find_package(xlnt REQUIRED)

set(LIB_SOURCES
    ${LIB_SOURCES_DIR}/parser/DataProcessorFactory.cpp
    ${LIB_SOURCES_DIR}/reader/ReaderFactory.cpp
    ${LIB_SOURCES_DIR}/writer/WriterFactory.cpp
)

add_library(SageDocsLib ${LIB_SOURCES})

target_include_directories(SageDocsLib PUBLIC ${LIB_SOURCES_DIR})

target_link_libraries(SageDocsLib PRIVATE csvmonkey::csvmonkey pugixml::pugixml xlnt::xlnt)
