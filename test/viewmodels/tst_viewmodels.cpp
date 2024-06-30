#include <QtTest>

#include "aimodelviewmodel.h"

#include "fdeepdataloader.h"
#include "unknownlayerviewmodel.h"
#include "denselayerviewmodel.h"

#include "fdeepmodelloader.h"

class ViewModelsTest : public QObject
{
    Q_OBJECT

private:
    ModelBridge::ModelPtr m_model;

private slots:
    void initTestCase();

    void testModelLoad();

    void testDenseLayerOutputs();

    void cleanupTestCase() {};
};

void ViewModelsTest::initTestCase()
{
    FdeepModelLoader loader;
    m_model = loader.loadModelFromFile("simple_image_classifier.json");
    QVERIFY(m_model);
}

void ViewModelsTest::testModelLoad()
{
    AIModelViewModel viewModel(m_model);

    QCOMPARE(viewModel.rowCount(), 4);

    // check for proper layer information
    auto index = viewModel.index(0,0);
    LayerViewModelInterface* layerVm = nullptr;
    QCOMPARE(viewModel.data(index,AIModelViewModel::layerId).toString(), "input_1");
    QCOMPARE(viewModel.data(index,AIModelViewModel::layerType).toString(), "unknown");
    layerVm = viewModel.data(index,AIModelViewModel::layerViewModel).value<LayerViewModelInterface*>();
    QVERIFY(layerVm);
    QVERIFY(dynamic_cast<UnknownLayerViewModel*>(layerVm));

    index = viewModel.index(1,0);
    layerVm = nullptr;
    QCOMPARE(viewModel.data(index,AIModelViewModel::layerId).toString(), "flatten");
    QCOMPARE(viewModel.data(index,AIModelViewModel::layerType).toString(), "unknown");
    layerVm = viewModel.data(index,AIModelViewModel::layerViewModel).value<LayerViewModelInterface*>();
    QVERIFY(layerVm);
    QVERIFY(dynamic_cast<UnknownLayerViewModel*>(layerVm));

    index = viewModel.index(2,0);
    layerVm = nullptr;
    QCOMPARE(viewModel.data(index,AIModelViewModel::layerId).toString(), "dense");
    QCOMPARE(viewModel.data(index,AIModelViewModel::layerType).toString(), "dense");
    layerVm = viewModel.data(index,AIModelViewModel::layerViewModel).value<LayerViewModelInterface*>();
    QVERIFY(layerVm);
    QVERIFY(dynamic_cast<DenseLayerViewModel*>(layerVm));

    index = viewModel.index(3,0);
    layerVm = nullptr;
    QCOMPARE(viewModel.data(index,AIModelViewModel::layerId).toString(), "dense_1");
    QCOMPARE(viewModel.data(index,AIModelViewModel::layerType).toString(), "dense");
    layerVm = viewModel.data(index,AIModelViewModel::layerViewModel).value<LayerViewModelInterface*>();
    QVERIFY(layerVm);
    QVERIFY(dynamic_cast<DenseLayerViewModel*>(layerVm));
}

void ViewModelsTest::testDenseLayerOutputs()
{
    // create dense viewmodel
    auto layer_interface = m_model->getLayer("dense_1");
    QVERIFY(layer_interface);
    auto dense_interface = std::dynamic_pointer_cast<ModelBridge::DenseLayerInterface>(layer_interface);
    QVERIFY(dense_interface);
    DenseLayerViewModel view_model(dense_interface);

    QFile testImageCsv("fashion-mnist_test.csv");
    testImageCsv.open(QFile::ReadOnly);

    // read labels
    testImageCsv.readLine();

    // read and split test data
    auto testImageData = testImageCsv.readLine().split(',');

    // Contains label followed by all pixel data
    QVERIFY(testImageData.length() == 28*28+1);

    int truthIndex = testImageData[0].toInt();

    // fill input vector with test image
    std::vector<double> inputImage(28*28,0.0);
    std::transform(testImageData.cbegin() + 1, testImageData.cend(), inputImage.begin(), [](const QString& pixelData){
        return double(pixelData.toInt());
    });

    // create data item
    FdeepDataLoader data_loader;
    auto data_cache = data_loader.createBlankData();
    QVERIFY(data_cache);
    QVERIFY(!data_cache->hasValidOutput());
    QVERIFY(!data_cache->hasError());

    // set input to test image data
    data_cache->setInputs(inputImage);
    m_model->apply(data_cache);
    QVERIFY(data_cache->hasValidOutput());
    QVERIFY(!data_cache->hasError());

    view_model.assignRunData(data_cache);

    // verify output layer length (only valid after data is assigned)
    QCOMPARE(view_model.getNodesListModel()->rowCount(), 10);
    // check that the max value occurs at the expected index
    double maxVal = -INT_MAX;
    double maxIndex = -1;

    for (int i = 0; i < view_model.getNodesListModel()->rowCount(); ++i) {
        bool wasDouble;
        double testVal = view_model.getNodesListModel()->data(view_model.getNodesListModel()->index(truthIndex,0), DenseNodesListModel::Roles::output).toDouble(&wasDouble);
        QVERIFY(wasDouble);
        if (testVal > maxVal) {
            maxVal = testVal;
            maxIndex = i;
        }
    }
    QCOMPARE(truthIndex, maxIndex);

    // verify hidden layer length
    layer_interface = m_model->getLayer("dense");
    QVERIFY(layer_interface);
    auto dense_interface1 = std::dynamic_pointer_cast<ModelBridge::DenseLayerInterface>(layer_interface);
    QVERIFY(dense_interface1);
    DenseLayerViewModel view_model1(dense_interface1);

    view_model1.assignRunData(data_cache);

    QCOMPARE(view_model1.getNodesListModel()->rowCount(), 128);
}

QTEST_MAIN(ViewModelsTest)

#include "tst_viewmodels.moc"
