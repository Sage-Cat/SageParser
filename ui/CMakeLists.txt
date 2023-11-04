project(DocsParserUi)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Locate Qt packages
find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)
find_package(Qt6Gui REQUIRED)
find_package(Qt6Quick REQUIRED)
find_package(Qt6 COMPONENTS QuickControls2 REQUIRED)

# Create client executable
add_executable(DocsParserUi ${ALL_CLIENT_SOURCES} ${RESOURCE_FILES})

# Include directories
target_include_directories(DocsParserUi PUBLIC ${CORE_SOURCES_DIR})

# Link libraries 
target_link_libraries(DocsParserUi Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Quick Qt6::QuickControls2 DocsParserLib::DocsParserLib)

# Set the destination directory for the executable
set_target_properties(DocsParserUi PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CLIENT_BUILD_DIR}/bin)
