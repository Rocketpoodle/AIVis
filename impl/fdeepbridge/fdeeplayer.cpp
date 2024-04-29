#include "fdeeplayer.h"
#include "fdeep/layers/dense_layer.hpp"

using namespace FdeepBridge;

Layer::Layer(const fdeep::internal::layer_ptr& layer)
    : m_layer(layer)
    , m_layer_type(getLayerTypeFromFbridgeLayer(layer))
{

}

std::string Layer::getId() const
{
    return m_layer->name_;
}

ModelBridge::LayerType Layer::getLayerType() const
{
    return m_layer_type;
}

fdeep::internal::layer_ptr Layer::getFdeepLayer() const
{
    return m_layer;
}

ModelBridge::LayerType FdeepBridge::getLayerTypeFromFbridgeLayer(const fdeep::internal::layer_ptr& fbridgeLayerPtr)
{
    if (std::dynamic_pointer_cast<fdeep::internal::dense_layer>(fbridgeLayerPtr)) {
        return ModelBridge::Dense;
    }

    return ModelBridge::Unknown;
}
