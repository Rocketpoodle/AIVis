#include <QGuiApplication>
#include <QQmlApplicationEngine>

// remove eventually
#include "ext_data_model.h"
#include "fdeepmodel.h"
#include <aimodelviewmodel.h>
#include <QQmlEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    /*!
     * \todo create function in fdeepbridge to construct a model from a given file
     */
    auto model = fdeep::load_ext_data_model("simple_image_classifier.json");
    auto m_model = std::make_shared<FdeepBridge::Model>(model);
    m_model->initialize();

    auto ifacePtr = std::dynamic_pointer_cast<ModelBridge::ModelInterface>(m_model); // why can't this implicitly convert to parent pointer??
    AIModelViewModel viewModel(ifacePtr);

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
