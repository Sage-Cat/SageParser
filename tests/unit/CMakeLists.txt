set(UNIT_TESTS_SOURCES 
    ${UNIT_TESTS_DIR}/CsvReaderTest.cpp
    ${UNIT_TESTS_DIR}/CsvWriterTest.cpp
    ${UNIT_TESTS_DIR}/DefaultTableProcessorTest.cpp
)

include_directories(${LIB_SOURCES})

foreach(test_source ${UNIT_TESTS_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)

    add_executable(${test_name} ${test_source})
    target_link_libraries(${test_name} SageParserLib GTest::GTest GTest::Main)
    
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
