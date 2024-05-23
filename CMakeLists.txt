cmake_minimum_required(VERSION 3.16)

project(ProjectTemplate VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

#
# Set up project properties
#

# Define main target based on project name to change it easily
set(MAIN_TARGET_NAME app${CMAKE_PROJECT_NAME})
set(MAIN_TARGET_URI  ${CMAKE_PROJECT_NAME})

set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Qml)

# Set QT_IMPORT_PATH
set(QML_IMPORT_PATH
    ${QT_QML_OUTPUT_DIRECTORY}
    CACHE
    STRING ""
    FORCE
)

# NO_CACHEGEN is set for qt_add_qml_module() in DEBUG mode so we can have a better QML Preview
# functionality (Only Qt6.6 and later)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(MODULE_CACHEGEN_STATE
        NO_CACHEGEN
    )
endif()

#
# Intialize the project
#

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(${MAIN_TARGET_NAME}
    Src/main.cpp
)

qt_add_qml_module(${MAIN_TARGET_NAME}
    URI ProjectTemplate
    ${MODULE_CACHEGEN_STATE}
    VERSION 1.0

    QML_FILES
        Qml/Main.qml
)

#
# Add submodules here
#

add_subdirectory(Res/)

#
# Target related properties and definitions
#

# Pass main target uri to C++
target_compile_definitions(${MAIN_TARGET_NAME} PRIVATE
    MAIN_MODULE="${MAIN_TARGET_URI}"
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(${MAIN_TARGET_NAME} PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${MAIN_TARGET_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(${MAIN_TARGET_NAME} PRIVATE
    Qt6::Quick
    appResources
)

include(GNUInstallDirs)
install(TARGETS ${MAIN_TARGET_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
