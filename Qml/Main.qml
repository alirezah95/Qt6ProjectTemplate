import QtQuick

import Application.Style

/*!
 * Application's main window
 */
ApplicationWindow {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Project Template")

    //* Load fonts
    //* ************************************/
    FontLoader { source: "qrc:/qt/qml/ProjectTemplate/Res/Fonts/fa-brands-400.ttf" }
    FontLoader { source: "qrc:/qt/qml/ProjectTemplate/Res/Fonts/fa-regular-400.ttf" }
    FontLoader { source: "qrc:/qt/qml/ProjectTemplate/Res/Fonts/fa-solid-900.ttf" }
}
