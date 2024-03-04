set(COMPONENT_TESTS_SOURCES 
    ${COMPONENT_TESTS_DIR}/CsvParserBuilderTest.cpp
    ${COMPONENT_TESTS_DIR}/XmlParserBuilderTest.cpp
)

foreach(test_source ${COMPONENT_TESTS_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)

    add_executable(${test_name} ${test_source})
    target_include_directories(${test_name} PUBLIC ${LIB_SOURCES_DIR} ${UTILS_DIR})
    target_link_libraries(${test_name} SageParserLib pugixml::pugixml GTest::GTest GTest::Main)
    
    add_test(NAME COMPONENT_${test_name} COMMAND ${test_name})
endforeach()
