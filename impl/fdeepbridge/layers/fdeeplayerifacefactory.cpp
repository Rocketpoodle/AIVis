#include "fdeeplayerifacefactory.h"

#include "layers/fdeepunknownlayer.h"
#include "layers/fdeepdenselayer.h"

using namespace FdeepBridge;

FdeepLayerFactory::FdeepLayerFactory()
{
    // register default layer creators
    registerLayerCreator(create_dense_fdeep_layer);
}

/*!
 * \brief FdeepLayerFactory::createBridgeInterface
 * \param layer fdeep layer pointer
 * \return ModelBridge::LayerInterface pointer constructed from the given layer
 */
LayerIfacePtr FdeepLayerFactory::createBridgeInterface(const fdeep::internal::layer_ptr& layer)
{
    if (!layer) {
        return nullptr;
    }

    LayerIfacePtr newLayer;

    // use first valid layer constructed
    auto creatorIt = m_layer_creators.cbegin();
    while (creatorIt != m_layer_creators.cend()) {
        if((newLayer = (*creatorIt)(layer))) {
            return newLayer;
        }
        ++creatorIt;
    }

    /*!
     * \note
     * Any unidentified layers can be created as unknown layer type
     */
    return std::make_shared<FdeepUnknownLayer>(layer);
}

/*!
 * \brief FdeepLayerFactory::registerLayerCreator
 * \param creator
 * \note I would love for this to use a map from the string type to the layer type
 *       string to the creator function. However, there isn't a good way to dynamically
 *       get the layer type id string from an fdeep layer pointer, and build up this
 *       list dynamically, so we can just rely on a list to be added to.
 */
void FdeepLayerFactory::registerLayerCreator(LayerCreator creator)
{
    m_layer_creators.push_back(creator);
}
