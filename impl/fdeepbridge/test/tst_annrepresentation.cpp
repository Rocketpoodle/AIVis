#include "fdeepdata.h"
#include "fdeepmodel.h"
#include <QtTest>
#include <fdeep/fdeep.hpp>
#include <iostream>

#include <ext_data_model.h>
#include <external_output_dict.h>

class ANNRepresentationTest : public QObject
{
    Q_OBJECT

private slots:
    void test_1();
};

void ANNRepresentationTest::test_1()
{
    auto model = fdeep::load_ext_data_model("simple_image_classifier.json");
    // auto inputs = model.generate_dummy_inputs();
    FdeepBridge::Model model_iface(model);
    model_iface.initialize();
    auto data_cache = std::dynamic_pointer_cast<ModelBridge::DataInterface>(std::make_shared<FdeepBridge::Data>());
    data_cache->setInputs(std::vector<double>(28*28,0.0));
    model_iface.apply(data_cache);
    auto outputs = data_cache->getLayerOutput(model_iface.getLayer("dense_1"));
    std::for_each(outputs.cbegin(), outputs.cend(), [](const double& a){
        qDebug() << a;
    });
    // fdeep::internal::output_dict output_cache;
    // model.predict_ext(inputs, output_cache);
    // fdeep::internal::node_connection conn("dense", 0, 0);
    // for (const auto& val : output_cache[conn.without_tensor_idx()]) {
    //     for (const auto& val2 : *(val.as_vector()))
    //     {
    //         qDebug() << val2;
    //     }
    // }
}

QTEST_MAIN(ANNRepresentationTest)

#include "tst_annrepresentation.moc"
