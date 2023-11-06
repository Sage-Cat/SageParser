find_package(GTest REQUIRED)

add_executable(TestSageDocsLib ${TEST_SOURCES_DIR}/testSageDocsLib.cpp)

target_include_directories(TestSageDocsLib PUBLIC ${LIB_SOURCES})

target_link_libraries(TestSageDocsLib SageDocsLib)
target_link_libraries(TestSageDocsLib GTest::GTest GTest::Main)

add_test(NAME TestSageDocsLib COMMAND TestSageDocsLib)

# Move test files to exetutable directory
# set(RESOURCES_DIR "${CMAKE_SOURCE_DIR}/tests/resources")
# file(COPY ${RESOURCES_DIR} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})