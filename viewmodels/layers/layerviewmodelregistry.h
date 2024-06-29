#ifndef LAYERVIEWMODELREGISTRY_H
#define LAYERVIEWMODELREGISTRY_H

#include <LayerInterface.h>

#include "layerviewmodelinterface.h"

#include <utils.h>

#include <QMap>

using LayerIfacePtr = std::shared_ptr<ModelBridge::LayerInterface>;
// For viewmodels we can use QObject parenting instead of shared pointers for cleanup
using LayerViewModelCreator = std::function<LayerViewModelInterface* (const LayerIfacePtr&, QObject* parent)>;

class LayerViewModelRegistry
{
public:
    LayerViewModelRegistry();

    LayerViewModelInterface* createLayerViewModel(const LayerIfacePtr& layer, QObject* parent = nullptr) const;

    void registerLayerViewModelCreator(const std::string& layerType, LayerViewModelCreator layerCreator);

private:
    QMap<std::string, LayerViewModelCreator> m_layer_viewmodel_creators;
};

CREATE_SINGLETON(LayerViewModelRegistry, LayerViewModelRegistrySingleton);

#endif // LAYERVIEWMODELREGISTRY_H
