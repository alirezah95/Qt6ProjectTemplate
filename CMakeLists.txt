cmake_minimum_required(VERSION 3.30)

project(ProjectTemplate VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)

#
# Set up project properties
#

# Define main target based on project name to change it easily
set(MAIN_TARGET_NAME app${CMAKE_PROJECT_NAME})
set(QML_MODULE_URI  ${CMAKE_PROJECT_NAME}.Qml)
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Qml)

# Set QT_IMPORT_PATH
set(QML_IMPORT_PATH
    ${QT_QML_OUTPUT_DIRECTORY}
    CACHE
    STRING ""
    FORCE
)

#
# Intialize the project
#

find_package(Qt6 6.5 REQUIRED COMPONENTS Qml Core Quick Gui)
qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(${MAIN_TARGET_NAME}
    src/main.cpp
)

#
# Add submodules here
#

add_subdirectory(src/)
add_subdirectory(qml/)
add_subdirectory(qml/style)
add_subdirectory(res/)


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
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    appQml
    appBackend
    appRes
    ApplicationStyleplugin
)

include(GNUInstallDirs)
install(TARGETS ${MAIN_TARGET_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
