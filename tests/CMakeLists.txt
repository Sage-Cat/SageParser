find_package(GTest REQUIRED)

set(UNIT_TESTS_DIR "${TEST_SOURCES_DIR}/unit")
set(COMPONENT_TESTS_DIR "${TEST_SOURCES_DIR}/component")

# Move test files to exetuTable directory
# set(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test_resources")
# file(COPY ${RESOURCES_DIR} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
# add_definitions(-DTEST_RESOURCES_DIR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_resources")

# add_subdirectory(component)
add_subdirectory(unit)