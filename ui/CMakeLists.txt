project(SageParserUi)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Locate Qt packages
find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)
find_package(Qt6Gui REQUIRED)

set(UI_SOURCES 
    ${UI_SOURCES_DIR}/main.cpp
    ${UI_SOURCES_DIR}/MainWindow.cpp
    ${UI_SOURCES_DIR}/TaskSelectionWidget.cpp
    ${UI_SOURCES_DIR}/DynamicInputForm.cpp
    ${UI_SOURCES_DIR}/ProgressDialog.cpp
    ${UI_SOURCES_DIR}/TaskSelectionWidget.cpp
    ${UI_SOURCES_DIR}/TaskManager.cpp
    ${UI_SOURCES_DIR}/TaskWorker.cpp

    # Forms
    ${UI_SOURCES_DIR}/Forms/TaskForm.hpp
    ${UI_SOURCES_DIR}/Forms/OdooProductsForm.cpp
)

# Create client executable
add_executable(SageParserUi ${UI_SOURCES})

# Include directories
target_include_directories(SageParserUi PUBLIC ${UI_SOURCES_DIR} ${LIB_SOURCES_DIR})

# Link libraries 
target_link_libraries(SageParserUi SageParserLib Qt6::Core Qt6::Widgets Qt6::Gui)
