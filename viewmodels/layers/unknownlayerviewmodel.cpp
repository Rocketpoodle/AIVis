#include "unknownlayerviewmodel.h"

UnknownLayerViewModel::UnknownLayerViewModel(const std::shared_ptr<ModelBridge::LayerInterface>& layer, QObject *parent)
    : LayerViewModelInterface{parent}
    , m_layer(layer)
{

}

UnknownLayerViewModel* create_unknown_layer_viewmodel(const std::shared_ptr<ModelBridge::LayerInterface>& layer, QObject* parent)
{
    if (!layer) {
        return nullptr;
    }

    return new UnknownLayerViewModel(layer, parent);
}
