cmake_minimum_required(VERSION 3.30)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_add_qml_module(appQml
    URI ${QML_MODULE_URI}
    VERSION 1.0

    QML_FILES
        Main.qml
)

target_link_libraries(${MAIN_TARGET_NAME} PRIVATE
    Qt6::Quick
)
