#include "fdeeplayerifacefactory.h"

#include "fdeepdenselayer.h"
#include "layers/fdeepunknownlayer.h"

using namespace FdeepBridge;

// Begin static layer creators

static LayerIfacePtr create_dense_fdeep_layer(const fdeep::internal::layer_ptr& layer)
{
    if (auto dense_ptr = std::dynamic_pointer_cast<fdeep::internal::dense_layer>(layer)) {
        return std::make_shared<DenseLayer>(dense_ptr);
    }

    return nullptr;
}

// End static layer creators

FdeepLayerFactory::FdeepLayerFactory()
{
    registerLayerCreator(create_dense_fdeep_layer);
}

LayerIfacePtr FdeepLayerFactory::createBridgeInterface(const fdeep::internal::layer_ptr& layer)
{
    if (!layer) {
        return nullptr;
    }

    LayerIfacePtr newLayer;

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
