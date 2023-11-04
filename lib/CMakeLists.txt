project(DocsParserLib)

set(CORE_SOURCES
    # ${CORE_SOURCES_DIR}/Dataset.cpp
)

add_library(DocsParserLib ${CORE_SOURCES})

target_link_libraries(core PRIVATE csvmonkey pugixml xlnt)