cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
option(BUILD_TESTING "Build the testing tree." ON)

set(CORE_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(UI_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ui")

# SUBDIRS
add_subdirectory(lib)
add_subdirectory(ui)
add_subdirectory(tests)