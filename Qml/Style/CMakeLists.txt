cmake_minimum_required(VERSION 3.16)

project(ApplicationStyle VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)

set_source_files_properties(
    Style.qml
    FAIcons.qml

    PROPERTIES
        QT_QML_SINGLETON_TYPE True
)

# NO_CACHEGEN is set for qt_add_qml_module() in DEBUG mode so we can have a better QML Preview
# functionality (Only Qt6.6 and later)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(MODULE_CACHEGEN_STATE
        NO_CACHEGEN
    )
endif()

qt_add_qml_module(ApplicationStyle
    URI Application.Style
    STATIC
    ${MODULE_CACHEGEN_STATE}
    VERSION 1.0
    IMPORTS QtQuick.Controls.Material
    QML_FILES
        Style.qml
        FAIcons.qml

        TextFontAwesome.qml

    SOURCES
        Src/BindableVar.h
        Src/BindableVar.cpp
)

qt_add_qml_module(ApplicationStyleImpl
    URI Application.Style.impl
    STATIC
    VERSION 1.0
    ${MODULE_CACHEGEN_STATE}

    QML_FILES
        Impl/FontIconSize.qml
)

target_include_directories(ApplicationStyle PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Src
)

target_link_libraries(ApplicationStyle PUBLIC
    Qt6::Quick
    Qt6::QuickControls2
    ApplicationStyleImpl
)
