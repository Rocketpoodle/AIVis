#ifndef DENSELAYERINTERFACE_H
#define DENSELAYERINTERFACE_H

#include <LayerInterface.h>

namespace ModelBridge {

class DenseLayerInterface : public LayerInterface
{
public:
    DenseLayerInterface() {};

    std::string getLayerType() const override {
        return "dense";
    }

};

}
#endif // DENSELAYERINTERFACE_H
