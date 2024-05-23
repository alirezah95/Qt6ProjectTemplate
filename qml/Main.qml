import QtQuick

import Application.Style


/*!
 * Application's main window
 */
ApplicationWindow {
    id: mainWindow
    width: Style.appWidth
    height: Style.appHeight
    visible: true
    title: qsTr("Project Template")

    //* Load fonts
    //* ************************************/
    FontLoader { source: "qrc:/qt/qml/ProjectTemplate/Res/fonts/fa-brands-400.ttf" }
    FontLoader { source: "qrc:/qt/qml/ProjectTemplate/Res/fonts/fa-regular-400.ttf" }
    FontLoader { source: "qrc:/qt/qml/ProjectTemplate/Res/fonts/fa-solid-900.ttf" }
}
