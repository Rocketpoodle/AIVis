#include "fdeepdataloader.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>

// remove eventually
#include <fdeepmodelloader.h>
#include <aimodelviewmodel.h>
#include <QQmlEngine>
#include <QQmlContext>

#include <QFile>//

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    /*!
     * \todo Remove this main
     *       Currently, we just load a known test model and run a known input through it,
     *       then manually assign the data to each layer
     */
    FdeepModelLoader model_loader;
    auto m_model = model_loader.loadModelFromFile("simple_image_classifier.json");

    AIModelViewModel viewModel(m_model);

    QFile testImageCsv("fashion-mnist_test.csv");
    testImageCsv.open(QFile::ReadOnly);
    // read labels
    testImageCsv.readLine();
    // read and split test data
    auto testImageData = testImageCsv.readLine().split(',');
    // fill input vector with test image
    std::vector<double> inputImage(28*28,0.0);
    std::transform(testImageData.cbegin() + 1, testImageData.cend(), inputImage.begin(), [](const QString& pixelData){
        return double(pixelData.toInt());
    });

    FdeepDataLoader data_loader;
    auto data = data_loader.createBlankData();
    data->setInputs(inputImage);
    m_model->apply(data);

    // a little known magic to assign the layer data (later this will be managed by a data handler)
    for (int i = 0; i < viewModel.rowCount(); ++i) {
        viewModel.data(viewModel.index(i,0), AIModelViewModel::layerViewModel).value<LayerViewModelInterface*>()->assignRunData(data);
    }

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
