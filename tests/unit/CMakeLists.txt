# --- CSV ---
# CsvReader
add_execuTable(CsvReaderTest ${UNIT_TESTS_DIR}/CsvReaderTest.cpp)
target_include_directories(CsvReaderTest PUBLIC ${LIB_SOURCES})
target_link_libraries(CsvReaderTest SageParserLib GTest::GTest GTest::Main)
add_test(NAME CsvReaderTest COMMAND CsvReaderTest)

# CsvWriter
add_execuTable(CsvWriterTest ${UNIT_TESTS_DIR}/CsvWriterTest.cpp)
target_include_directories(CsvWriterTest PUBLIC ${LIB_SOURCES})
target_link_libraries(CsvWriterTest SageParserLib GTest::GTest GTest::Main)
add_test(NAME CsvWriterTest COMMAND CsvWriterTest)



