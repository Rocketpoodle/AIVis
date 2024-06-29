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

std::shared_ptr<ModelBridge::LayerInterface> create_dense_fdeep_layer( const fdeep::internal::layer_ptr& layer);

}
#endif // FDEEPDENSELAYER_H
