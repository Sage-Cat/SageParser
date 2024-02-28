find_package(GTest REQUIRED)

set(UNIT_TESTS_DIR "${TEST_SOURCES_DIR}/unit")
set(COMPONENT_TESTS_DIR "${TEST_SOURCES_DIR}/component")

# add_subdirectory(component)
add_subdirectory(unit)