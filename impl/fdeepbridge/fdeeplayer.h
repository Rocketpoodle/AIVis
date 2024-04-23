#ifndef FDEEPLAYER_H
#define FDEEPLAYER_H

#include "fdeep/node.hpp"
#include <LayerInterface.h>

namespace FdeepBridge {

class Layer : public ModelBridge::LayerInterface
{
public:
    Layer(const fdeep::internal::layer_ptr& layer);

    virtual std::string getId() const override;

    virtual ModelBridge::LayerType getLayerType() const override;

    fdeep::internal::layer_ptr getFdeepLayer() const;

private:
    fdeep::internal::layer_ptr m_layer;
    ModelBridge::LayerType m_layer_type;
};
}
#endif // FDEEPLAYER_H
