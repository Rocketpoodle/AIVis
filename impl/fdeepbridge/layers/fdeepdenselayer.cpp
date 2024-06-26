#include "fdeepdenselayer.h"

#include "FdeepInternalRep.h"

using namespace FdeepBridge;

DenseLayer::DenseLayer(const dense_layer_ptr& layer)
    : m_layer(layer)
{

}

std::string DenseLayer::getId() const
{
    return m_layer->name_;
}

std::shared_ptr<ModelBridge::InternalLayerRep> DenseLayer::getInternalRep() const
{
    return std::make_shared<FdeepInternalRep>(m_layer);
}
