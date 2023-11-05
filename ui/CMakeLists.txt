project(SageDocsUi)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Locate Qt packages
find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)
find_package(Qt6Gui REQUIRED)
find_package(Qt6Quick REQUIRED)
find_package(Qt6 COMPONENTS QuickControls2 REQUIRED)

set(UI_SOURCES 
    ${UI_SOURCES_DIR}/main.cpp
    ${UI_SOURCES_DIR}/SageDocsUi.cpp
)

# Create client executable
add_executable(SageDocsUi ${UI_SOURCES})

# Include directories
target_include_directories(SageDocsUi PUBLIC ${UI_SOURCES_DIR} ${LIB_SOURCES_DIR})

# Link libraries 
target_link_libraries(SageDocsUi SageDocsLib Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Quick Qt6::QuickControls2)
