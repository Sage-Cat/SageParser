set(UNIT_TESTS_SOURCES 
    ${UNIT_TESTS_DIR}/CsvReaderTest.cpp
    ${UNIT_TESTS_DIR}/CsvWriterTest.cpp
    ${UNIT_TESTS_DIR}/XmlReaderTest.cpp
    ${UNIT_TESTS_DIR}/XmlWriterTest.cpp
    ${UNIT_TESTS_DIR}/DefaultTableProcessorTest.cpp
)

foreach(test_source ${UNIT_TESTS_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)

    add_executable(${test_name} ${test_source})
    target_include_directories(${test_name} PUBLIC ${LIB_SOURCES_DIR} ${UTILS_DIR})
    target_link_libraries(${test_name} SageParserLib pugixml::pugixml GTest::GTest GTest::Main)
    
    add_test(NAME UNIT_${test_name} COMMAND ${test_name})
endforeach()
