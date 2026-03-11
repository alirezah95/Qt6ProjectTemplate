cmake_minimum_required(VERSION 3.30)

#
# Target related properties and definitions
#
# Pass main target uri to C++
target_compile_definitions(${MAIN_TARGET_NAME} PRIVATE
    QML_MODULE_URI="${QML_MODULE_URI}"
)

qt_add_qml_module(appBackend
    URI ${CMAKE_PROJECT_NAME}.Backend
    VERSION 1.0

    SOURCES
)
