# Test for the whole SageParser library
add_execuTable(TestSageParser ${TEST_SOURCES_DIR}/testSageParser.cpp)
target_include_directories(TestSageParserLib PUBLIC ${LIB_SOURCES})
target_link_libraries(TestSageParserLib SageParserLib GTest::GTest GTest::Main)
add_test(NAME TestSageParserLib COMMAND TestSageParserLib)