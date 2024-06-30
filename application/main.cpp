#include <QGuiApplication>
#include <QQmlApplicationEngine>

// remove eventually
#include <fdeepmodelloader.h>
#include <aimodelviewmodel.h>
#include <QQmlEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    /*!
     * \todo create function in fdeepbridge to construct a model from a given file
     */
    FdeepModelLoader model_loader;
    auto m_model = model_loader.loadModelFromFile("simple_image_classifier.json");

    AIModelViewModel viewModel(m_model);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    /*!
     * \todo root injection is BAD remove once backend singleton entrypoing is created
     */
    engine.rootContext()->setContextProperty("aiViewModel", &viewModel);

    engine.loadFromModule("AIVis", "Main");

    return app.exec();
}
