#pragma once

#include <QObject>
#include <QQmlEngine>

/*!
 * \brief The BindableInt class provides an int that can be binded in Qml and also changed from C++
 * so that the binding is not broken
 */
class BindableInt : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int value MEMBER mValue NOTIFY valueChanged)
    QML_ELEMENT

public:
    explicit BindableInt(QObject* parent = nullptr) : QObject { parent } { }

    int value() const { return mValue; }
    Q_INVOKABLE void setValue(const int& newValue)
    {
        if (mValue == newValue) {
            return;
        }

        mValue = newValue;
        emit valueChanged();
    }

signals:
    void valueChanged();

private:
    int mValue;
};


/*!
 * \brief The BindableReal class provides a qreal that can be binded in Qml and also changed from
 * C++ so that the binding is not broken
 */
class BindableReal : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal value MEMBER mValue NOTIFY valueChanged)
    QML_ELEMENT

public:
    explicit BindableReal(QObject* parent = nullptr) : QObject { parent } { }

    qreal value() const { return mValue; }
    Q_INVOKABLE void setValue(const qreal& newValue)
    {
        if (mValue == newValue) {
            return;
        }

        mValue = newValue;
        emit valueChanged();
    }

signals:
    void valueChanged();

private:
    qreal mValue;
};


/*!
 * \brief The BindableVariant class provides a variant that can be binded in Qml and also changed
 * from C++ so that the binding is not broken
 */
class BindableVariant : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant value MEMBER mValue NOTIFY valueChanged)
    QML_ELEMENT

public:
    explicit BindableVariant(QObject* parent = nullptr) : QObject { parent } { }

    QVariant value() const { return mValue; }
    Q_INVOKABLE void setValue(const QVariant& newValue)
    {
        if (mValue == newValue) {
            return;
        }

        mValue = newValue;
        emit valueChanged();
    }

signals:
    void valueChanged();

private:
    QVariant mValue;
};
