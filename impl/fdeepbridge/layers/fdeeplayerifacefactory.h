#ifndef FDEEPLAYERIFACEFACTORY_H
#define FDEEPLAYERIFACEFACTORY_H

#include "fdeep/node.hpp"

#include <utils.h>

#include <LayerInterface.h>

using LayerIfacePtr = std::shared_ptr<ModelBridge::LayerInterface>;
using LayerCreator = std::function<LayerIfacePtr (const fdeep::internal::layer_ptr&)>;

namespace FdeepBridge {

class FdeepLayerFactory
{
public:
    FdeepLayerFactory();
    LayerIfacePtr createBridgeInterface(const fdeep::internal::layer_ptr& layer) const;

    void registerLayerCreator(LayerCreator creator);

private:
    std::list<LayerCreator> m_layer_creators;
};

CREATE_SINGLETON(FdeepLayerFactory, FdeepLayerFactorySingleton);

}
#endif // FDEEPLAYERIFACEFACTORY_H
