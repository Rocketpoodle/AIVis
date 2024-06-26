#ifndef FDEEPUNKNOWNLAYER_H
#define FDEEPUNKNOWNLAYER_H

#include "fdeep/node.hpp"
#include <LayerInterface.h>

namespace FdeepBridge {

/*!
 * \brief The FdeepUnknownLayer class
 * \details Catch-all layer type that can be used for un-implemented layers
 */
class FdeepUnknownLayer : public ModelBridge::LayerInterface
{
public:
    FdeepUnknownLayer(const fdeep::internal::layer_ptr& layer);

    std::string getId() const override;

    std::shared_ptr<ModelBridge::InternalLayerRep> getInternalRep() const override;

    std::string getLayerType() const override;

private:
    fdeep::internal::layer_ptr m_layer;
};
}
#endif // FDEEPUNKNOWNLAYER_H
