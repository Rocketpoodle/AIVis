#ifndef FDEEPDENSELAYER_H
#define FDEEPDENSELAYER_H

#include <layers/denselayerinterface.h>
#include "fdeep/layers/dense_layer.hpp"

using dense_layer_ptr = std::shared_ptr<fdeep::internal::dense_layer>;

namespace FdeepBridge {

class DenseLayer : public ModelBridge::DenseLayerInterface
{
public:
    DenseLayer(const dense_layer_ptr& layer);

    std::string getId() const override;

    std::shared_ptr<ModelBridge::InternalLayerRep> getInternalRep() const override;

private:
    dense_layer_ptr m_layer;
};

}
#endif // FDEEPDENSELAYER_H
