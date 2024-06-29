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

// Static method for factory construction
std::shared_ptr<ModelBridge::LayerInterface> FdeepBridge::create_dense_fdeep_layer(const fdeep::internal::layer_ptr& layer)
{
    if (auto dense_ptr = std::dynamic_pointer_cast<fdeep::internal::dense_layer>(layer)) {
        return std::make_shared<DenseLayer>(dense_ptr);
    }

    return nullptr;
}
