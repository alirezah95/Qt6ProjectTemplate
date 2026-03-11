#include <QQmlApplicationEngine>
#include <QGuiApplication>


int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    //! Use MAIN_MODULE from CMake for flexibility
    engine.loadFromModule(QML_MODULE_URI, "Main");

    return app.exec();
}
