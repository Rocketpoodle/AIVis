#include "fdeepmodel.h"
#include "layers/denselayerinterface.h"
#include <QtTest>
#include <fdeep/fdeep.hpp>
#include <QImage>
#include <QModelIndex>

#include <ext_data_model.h>
#include <external_output_dict.h>

#include <layers/denselayerviewmodel.h>

#include "fdeepdata.h"

class DenseLayerViewModelTest : public QObject
{
    Q_OBJECT

private:
    std::shared_ptr<FdeepBridge::Model> m_model;

private slots:
    void initTestCase();

    void testDataOutputs();

    void cleanupTestCase() {};
};

void DenseLayerViewModelTest::initTestCase()
{
    auto model = fdeep::load_ext_data_model("simple_image_classifier.json");
    m_model = std::make_shared<FdeepBridge::Model>(model);
    m_model->initialize();
}

void DenseLayerViewModelTest::testDataOutputs()
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
    auto data_cache = std::dynamic_pointer_cast<ModelBridge::DataInterface>(std::make_shared<FdeepBridge::Data>());
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

QTEST_MAIN(DenseLayerViewModelTest)

#include "tst_denselayerviewmodel.moc"
