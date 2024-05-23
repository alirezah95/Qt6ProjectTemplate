cmake_minimum_required(VERSION 3.16)

qt_add_qml_module(appResources
    URI ${MAIN_TARGET_URI}.Res
    VERSION 1.0
    STATIC

    RESOURCES
        Fonts/fa-brands-400.ttf
        Fonts/fa-regular-400.ttf
        Fonts/fa-solid-900.ttf
)

