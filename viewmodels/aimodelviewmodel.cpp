#include "aimodelviewmodel.h"

AIModelViewModel::AIModelViewModel(std::shared_ptr<ModelBridge::ModelInterface> &model, QObject *parent)
    : QAbstractListModel{parent}
    , m_model(model)
{
    std::for_each(model->getLayerGraph().cbegin(), model->getLayerGraph().cend(),
                  [this](const ModelBridge::LayerGraphNodePtr& layerNode){
                      /*!
                       * \todo determine if we need to check if layerNode->layer exists or if we can
                       *       assume it does at this point
                       */
                      m_layers.emplace_back(LayerViewModelRegistrySingleton::instance().createLayerViewModel(layerNode->layer, this));
                  });
}

AIModelViewModel::~AIModelViewModel()
{
    /*!
     * \note although we could use qDeleteAll(m_layers), we can also count
     *       on the ViewModels being destoyed as they are given this object
     *       as a parent QObject upon creation
     */
}

int AIModelViewModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return -1;
    }

    return m_layers.count();
}

QVariant AIModelViewModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= m_layers.size()) {
        return QVariant();
    }

    const auto* layerPtr = m_layers.at(index.row());

    switch (role)
    {
    case Roles::layer:
        return QVariant::fromValue(layerPtr);
    case Roles::id:
        return layerPtr->getLayerId();
    case Roles::type:
        return layerPtr->getLayerType();
    default:
        return QVariant();
    }
}
