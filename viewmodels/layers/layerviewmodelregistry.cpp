#include "layerviewmodelregistry.h"

#include "unknownlayerviewmodel.h"
#include "denselayerviewmodel.h"

LayerViewModelRegistry::LayerViewModelRegistry()
{
    registerLayerViewModelCreator("dense", create_dense_layer_viewmodel);
    registerLayerViewModelCreator("unknown", create_unknown_layer_viewmodel);
}

/*!
 * \brief LayerViewModelRegistry::createLayerViewModel
 * \param layer layer interface pointer to create viewmodel for
 * \return viewmodel for the given layer interface, null if the layer is null
 */
LayerViewModelInterface* LayerViewModelRegistry::createLayerViewModel(const LayerIfacePtr& layer, QObject* parent) const
{
    if (!layer) {
        return nullptr;
    }

    auto layerType = layer->getLayerType();

    // check if we have a viewmodel for the given layer type
    if (!m_layer_viewmodel_creators.contains(layerType)) {
        qDebug() << "No known layer creator for layer type: \'" << layerType << "\'";
        return (*create_unknown_layer_viewmodel)(layer, parent);
    }

    auto layerViewModel = m_layer_viewmodel_creators[layerType](layer, parent);

    // check if the layer creator succeeded
    if (!layer) {
        qDebug() << "Layer creator for type \'" << layer->getLayerType()
                 << "\' for layer id: \'" << layer->getId() << "\'";
        return (*create_unknown_layer_viewmodel)(layer, parent);
    }

    return layerViewModel;
}

/*!
 * \brief LayerViewModelRegistry::registerLayerViewModelCreator
 * \param layerType layer type string to register creation method for
 * \param layerCreator layer creator function
 */
void LayerViewModelRegistry::registerLayerViewModelCreator(const std::string& layerType, LayerViewModelCreator layerCreator)
{
    if (layerType == "") {
        qDebug() << "Cannot register layer creator with empty layer type";
        return;
    }

    m_layer_viewmodel_creators[layerType] = layerCreator;
}
