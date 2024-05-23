#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QGuiApplication>
#include <QScreen>

/*!
 * \brief The PlatformToolsls class provides some functionality related to the platform and screen of
 * the current device
 */
class PlatformTools : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal logicalDPI         READ   logicalDPI       CONSTANT)
    Q_PROPERTY(qreal physicalDPI        READ   physicalDPI      CONSTANT)
    Q_PROPERTY(qreal devicePixelRatio   READ   devicePixelRatio CONSTANT)
    Q_PROPERTY(qreal width              READ   width            CONSTANT)
    Q_PROPERTY(qreal height             READ   height           CONSTANT)
    Q_PROPERTY(qreal defaultFontPt      MEMBER mDefaultFontPt   CONSTANT)
    Q_PROPERTY(qreal secondaryFontPt    MEMBER mSecondaryFontPt CONSTANT)
    Q_PROPERTY(qreal tertiaryFontPt     MEMBER mTertiaryFontPt  CONSTANT)
    Q_PROPERTY(qreal fontRatio          MEMBER mFontRatio       CONSTANT)
    Q_PROPERTY(qreal sizeRatio          MEMBER mSizeRatio       CONSTANT)
    Q_PROPERTY(qreal isMobile           MEMBER mIsMobile        CONSTANT)

    QML_ELEMENT

public:
    explicit PlatformTools(QObject* parent=nullptr);

    Q_INVOKABLE qreal dp(qreal size) const;

    qreal logicalDPI() const;
    qreal physicalDPI() const;
    qreal devicePixelRatio() const;
    qreal width() const;
    qreal height() const;

private:
    const qreal cRefDpr;        //! \brief Reference device pixel ratio
    const qreal cRefDpi;        //! \brief Reference device logical dot per inch
    const qreal cRefPDpi;       //! \brief Reference device physical dot per inch
    const qreal cRefWidth;      //! \brief Reference device width
    const qreal cRefHeight;     //! \brief Reference device height

    bool  mIsMobile;
    qreal mAvailableWidth;
    qreal mAvailableHeight;
    qreal mDefaultFontPt = 14.;
    qreal mSecondaryFontPt = 12.;
    qreal mTertiaryFontPt = 10.5;
    qreal mFontRatio;
    qreal mSizeRatio;
};


//! For applications that are being developed for mobile only, its better to set size ratio to 1
//! when they are running on desktop (development host) and the font ratio is better to be related
//! to logical dots per inch (dpi)
inline PlatformTools::PlatformTools(QObject* parent)
    : QObject { parent }
    , cRefDpr { 2.75 }
    , cRefDpi { 72 }
    , cRefPDpi { 160.559 }
    , cRefWidth { 393 }
    , cRefHeight { 851 }
    , mFontRatio { 1 }
    , mSizeRatio { 1 }
{

    const QScreen* screen = QGuiApplication::primaryScreen();

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
    mIsMobile = true;

    qreal width = qMin(screen->geometry().width(), screen->geometry().height());
    qreal height = qMax(screen->geometry().width(), screen->geometry().height());
    qreal dpi = screen->logicalDotsPerInch();

    //! Setting size ratio
    mSizeRatio = qMin(height / cRefHeight, width / cRefWidth);

    //! Setting font sizes
    qreal heightRatio = height * cRefDpi / (dpi * cRefHeight);
    qreal widthRatio = width * cRefDpi / (dpi * cRefWidth);

    //! Setting font ratio
    mFontRatio = qMin(heightRatio, widthRatio);

    // qDebug() << "info: " << mSizeRatio << mFontRatio;
    mDefaultFontPt = qMin(15., qMax(12., mDefaultFontPt * mFontRatio));
    mSecondaryFontPt = qMin(13.5, qMax(10.5, mSecondaryFontPt * mFontRatio));
    mTertiaryFontPt = qMin(12., qMax(9., mTertiaryFontPt * mFontRatio));
#else
    mIsMobile = false;

    //! Setting size ratio
    mSizeRatio = 1;

    //! Setting font ratio
    mFontRatio = cRefDpi / screen->logicalDotsPerInch();

    mDefaultFontPt = mDefaultFontPt * mFontRatio;
    mSecondaryFontPt = mSecondaryFontPt * mFontRatio;
    mTertiaryFontPt = mTertiaryFontPt * mFontRatio;
#endif

    //! Setting available width and height
    mAvailableWidth = screen->availableSize().width();
    mAvailableHeight = screen->availableSize().height();
}

inline qreal PlatformTools::dp(qreal size) const
{
    return size * mSizeRatio;
}

inline qreal PlatformTools::logicalDPI() const
{
    return QGuiApplication::primaryScreen()->logicalDotsPerInch();
}

inline qreal PlatformTools::physicalDPI() const
{
    return QGuiApplication::primaryScreen()->physicalDotsPerInch();
}

inline qreal PlatformTools::devicePixelRatio() const
{
    return QGuiApplication::primaryScreen()->devicePixelRatio();
}

inline qreal PlatformTools::width() const
{
    return QGuiApplication::primaryScreen()->size().width();
}

inline qreal PlatformTools::height() const
{
    return QGuiApplication::primaryScreen()->size().height();
}
