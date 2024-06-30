#include "fdeepdataloader.h"
#include "fdeepmodel.h"
#include "layers/denselayerinterface.h"
#include "layers/fdeepdenselayer.h"
#include "layers/fdeepunknownlayer.h"
#include <QtTest>
#include <fdeep/fdeep.hpp>
#include <QImage>

#include <ext_data_model.h>
#include <external_output_dict.h>

#include "public/fdeepmodelloader.h"

class FdeepBridgeTest : public QObject
{
    Q_OBJECT

private:
    std::shared_ptr<FdeepBridge::Model> m_model;

private slots:
    void initTestCase();

    void testModelParams();

    void testLayerGraph();

    void testResult();

    void cleanupTestCase() {};
};

void FdeepBridgeTest::initTestCase()
{
    FdeepModelLoader loader;
    auto loaded_model = loader.loadModelFromFile("simple_image_classifier.json");
    QVERIFY(loaded_model);
    m_model = std::dynamic_pointer_cast<FdeepBridge::Model>(loaded_model);
    QVERIFY(m_model);
}

void FdeepBridgeTest::testModelParams()
{
    QVERIFY((m_model->getInputShape() == std::vector<int>{28,28}));
    QVERIFY((m_model->getOutputShape() == std::vector<int>{10}));
    QVERIFY(m_model->getLayerCount() == 4);
}

/*!
 * \brief FdeepBridgeTest::testLayerGraph
 * \details tests that layer graph has correct nodes and connections
 *          and is properly sorted
 */
void FdeepBridgeTest::testLayerGraph()
{
    int i = 0;
    for (const auto& layer: m_model->getLayerGraph()) {
        if (layer->layer->getId() == "input_1") {
            QCOMPARE(i, 0);
            QVERIFY(layer->outputs.back()->layer->getId() == "flatten");
            QVERIFY(layer->layer->getLayerType() == "unknown");
            QVERIFY(std::dynamic_pointer_cast<ModelBridge::LayerInterface>(layer->layer));
            QVERIFY(std::dynamic_pointer_cast<FdeepBridge::FdeepUnknownLayer>(layer->layer));
        }
        else if (layer->layer->getId() == "flatten") {
            QCOMPARE(i, 1);
            QVERIFY(layer->inputs.back()->layer->getId() == "input_1");
            QVERIFY(layer->layer->getLayerType() == "unknown");
            QVERIFY(std::dynamic_pointer_cast<ModelBridge::LayerInterface>(layer->layer));
            QVERIFY(std::dynamic_pointer_cast<FdeepBridge::FdeepUnknownLayer>(layer->layer));
        }
        else if (layer->layer->getId() == "dense") {
            QCOMPARE(i, 2);
            QVERIFY(layer->inputs.back()->layer->getId() == "flatten");
            QVERIFY(layer->outputs.back()->layer->getId() == "dense_1");
            QVERIFY(layer->layer->getLayerType() == "dense");
            QVERIFY(std::dynamic_pointer_cast<ModelBridge::DenseLayerInterface>(layer->layer));
            QVERIFY(std::dynamic_pointer_cast<FdeepBridge::DenseLayer>(layer->layer));
        }
        else if (layer->layer->getId() == "dense_1") {
            QCOMPARE(i, 3);
            QVERIFY(layer->inputs.back()->layer->getId() == "dense");
            QVERIFY(layer->layer->getLayerType() == "dense");
            QVERIFY(std::dynamic_pointer_cast<ModelBridge::DenseLayerInterface>(layer->layer));
            QVERIFY(std::dynamic_pointer_cast<FdeepBridge::DenseLayer>(layer->layer));
        }
        ++i;
    }
}

/*!
 * \brief FdeepBridgeTest::testResult
 * \details loads the test model and data and verifies that correct classification is made
 */
void FdeepBridgeTest::testResult()
{
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
    QVERIFY(!data_cache->hasValidOutput());
    QVERIFY(!data_cache->hasError());

    // set input to test image data
    data_cache->setInputs(inputImage);
    m_model->apply(data_cache);
    QVERIFY(data_cache->hasValidOutput());
    QVERIFY(!data_cache->hasError());

    auto outputs = data_cache->getLayerOutput(m_model->getLayer("dense_1"));

    // check that index of max likelihood matches truth index
    QVERIFY((std::max_element(outputs.cbegin(), outputs.cend()) - outputs.cbegin()) == truthIndex);
}

QTEST_MAIN(FdeepBridgeTest)

#include "tst_fdeepbridge.moc"
