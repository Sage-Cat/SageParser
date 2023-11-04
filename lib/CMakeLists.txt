project(SageDocsLib)

set(CORE_SOURCES
    # ${CORE_SOURCES_DIR}/Dataset.cpp
)

add_library(SageDocsLib ${CORE_SOURCES})

target_link_libraries(core PRIVATE csvmonkey pugixml xlnt)