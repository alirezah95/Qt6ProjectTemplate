cmake_minimum_required(VERSION 3.30)

qt_add_qml_module(appRes
    URI ${CMAKE_PROJECT_NAME}.Res
    VERSION 1.0

    RESOURCES
        fonts/fa-brands-400.ttf
        fonts/fa-regular-400.ttf
        fonts/fa-solid-900.ttf
)

