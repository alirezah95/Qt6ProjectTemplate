pragma Singleton

import QtQuick

import Application.Style
import Application.Style.impl

QtObject {
    id: style

    enum Theme {
        Light,
        Dark
    }

    property int        theme:                          Style.Theme.Light

    property color      background:                     _isLight ? "#FFFFFF"    : "#202020"
    property color      foreground:                     _isLight ? "#202020"    : "#FFFFFF"
    property color      accent:                         _isLight ? "#E91E63"    : "#F48FB1"
    property color      primary:                        _isLight ? "#3F51B5"    : "#9FA8DA"
    property color      secondary:                      _isLight ? "#2196F3"    : "#90CAF9"

    property color      hintTextColor:                  Material.hintTextColor

    //! Shortcut for checking theme
    readonly property bool _isLight:                    theme === Style.Theme.Light

    //! App specific shades of main colors (be default are based on Material)
    property color      red:            _isLight ? "#F44336" : "#EF9A9A"
    property color      pink:           _isLight ? "#E91E63" : "#F48FB1"
    property color      purple:         _isLight ? "#9C27B0" : "#CE93D8"
    property color      deepPurple:     _isLight ? "#673AB7" : "#B39DDB"
    property color      indigo:         _isLight ? "#3F51B5" : "#9FA8DA"
    property color      blue:           _isLight ? "#2196F3" : "#90CAF9"
    property color      lightBlue:      _isLight ? "#03A9F4" : "#81D4FA"
    property color      cyan:           _isLight ? "#00BCD4" : "#80DEEA"
    property color      teal:           _isLight ? "#009688" : "#80CBC4"
    property color      green:          _isLight ? "#4CAF50" : "#A5D6A7"
    property color      lightGreen:     _isLight ? "#8BC34A" : "#C5E1A5"
    property color      lime:           _isLight ? "#CDDC39" : "#E6EE9C"
    property color      yellow:         _isLight ? "#E0BF00" : "#FFF59D"
    property color      amber:          _isLight ? "#FFC107" : "#FFE082"
    property color      orange:         _isLight ? "#FF9800" : "#FFCC80"
    property color      deepOrange:     _isLight ? "#FF5722" : "#FFAB91"
    property color      brown:          _isLight ? "#795548" : "#BCAAA4"
    property color      grey:           _isLight ? "#9E9E9E" : "#EEEEEE"
    property color      blueGrey:       _isLight ? "#607D8B" : "#B0BEC5"


    //! PlatformTools instance
    readonly property PlatformTools     platformTools:      PlatformTools { }

    //! Font sizes
    readonly property real              defaultFontPt:      platformTools.defaultFontPt
    readonly property real              secondaryFontpt:    platformTools.secondaryFontPt
    readonly property real              tertiaryFontpt:     platformTools.tertiaryFontPt

    //! Number properties
    property int        elevation:          dp(6)
    property int        leftPadding:        dp(16)
    property int        rightPadding:       dp(16)
    property int        topPadding:         dp(10)
    property int        bottomPadding:      dp(10)
    property int        roundedCorners:     Material.MediumScale
    property int        borderWidth:        1
    property int        delegateHeight:     Material.delegateHeight
    property int        touchTarget:        Material.touchTarget

    //! Mobile specific properties
    readonly property bool  isMobile:                   platformTools.isMobile
    readonly property int   appWidth:                   isMobile ? Screen.desktopAvailableWidth : 393
    readonly property int   appHeight:                  isMobile ? Screen.desktopAvailableHeight : 777
    readonly property int   notAvailableHeight:         Screen.height - Screen.desktopAvailableHeight
    readonly property real  keyboardHeight:             Qt.inputMethod.visible
                                                        ? (Qt.inputMethod.keyboardRectangle.height
                                                           / platformTools.devicePixelRatio + notAvailableHeight / 2)
                                                        : 0

    //! Specific styles for some Controls
    readonly property FontIconSize fontIconSize: FontIconSize {
        largePt: Application.font.pointSize * 1.25
        normalPt: Application.font.pointSize * 1
        smallPt: Application.font.pointSize * 0.8
    }

    //* Methods
    //* ************************************/
    //! Using PlatformTools returns a size that is suitable for this screen
    function dp(size)
    {
        return platformTools.dp(size);
    }
}
