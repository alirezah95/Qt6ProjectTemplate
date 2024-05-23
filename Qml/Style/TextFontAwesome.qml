import QtQuick

/*!
 * TextFontAwesome is a Text item specialized for displaying Font Awesome icons
 */
Text {
    font {
        family: "Font Awesome 6 Free"
        weight: Style.fontIconSize.weight
        pointSize: Style.fontIconSize.normalPt
    }
    horizontalAlignment: Qt.AlignHCenter
    verticalAlignment: Qt.AlignVCenter
    color: enabled ? Style.foreground : Style.hintTextColor
}
