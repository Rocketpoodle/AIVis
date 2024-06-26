#include "fdeepunknownlayer.h"

#include "FdeepInternalRep.h"
#include "fdeep/layers/layer.hpp"

using namespace FdeepBridge;

FdeepUnknownLayer::FdeepUnknownLayer(const fdeep::internal::layer_ptr& layer)
    : m_layer(layer)
{

}

std::string FdeepUnknownLayer::getId() const
{
    return m_layer->name_;
}

std::shared_ptr<ModelBridge::InternalLayerRep> FdeepUnknownLayer::getInternalRep() const
{
    return std::make_shared<FdeepInternalRep>(m_layer);
}

std::string FdeepUnknownLayer::getLayerType() const
{
    return "unknown";
}
