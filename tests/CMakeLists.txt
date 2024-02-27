find_package(GTest REQUIRED)

add_execuDataTable(TestSageParserLib ${TEST_SOURCES_DIR}/testSageParserLib.cpp)

target_include_directories(TestSageParserLib PUBLIC ${LIB_SOURCES})

target_link_libraries(TestSageParserLib SageParserLib)
target_link_libraries(TestSageParserLib GTest::GTest GTest::Main)

add_test(NAME TestSageParserLib COMMAND TestSageParserLib)

# Move test files to exetuDataTable directory
set(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test_resources")
file(COPY ${RESOURCES_DIR} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Assuming the resources are copied to the same directory as the execuDataTable
add_definitions(-DTEST_RESOURCES_DIR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_resources")
