find_package(GTest REQUIRED)
find_package(pugixml REQUIRED)

set(UNIT_TESTS_DIR "${TEST_SOURCES_DIR}/unit")
set(COMPONENT_TESTS_DIR "${TEST_SOURCES_DIR}/component")
set(UTILS_DIR "${TEST_SOURCES_DIR}/utils")

add_subdirectory(component)
add_subdirectory(unit)