#include "denselayerviewmodel.h"

DenseNodesListModel::DenseNodesListModel(const std::shared_ptr<ModelBridge::DenseLayerInterface>& layer, QObject *parent)
    : m_layer(layer)
{

}

int DenseNodesListModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return -1;
    }

    /*! \note this assumes shape is always 1 column */
    /*! \note currently, with Fdeep, there is no way to acertain the node count
     *        from the dense layer. Instead, we can acertain this from the given
     *        stored data, so this will remain 0 until data has been assigned
     */
    return m_data.size();
}

QVariant DenseNodesListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= m_data.size()) {
        return QVariant();
    }

    switch (role)
    {
    case Roles::output:
        /*! \note this assumes shape is always 1 column
         *        we should likely get layer shape info and use that
         *        although it could be saved for other layer model impls
         */
        return m_data[index.row()];
    default:
        return QVariant();
    }
}

void DenseNodesListModel::assignRunData(const std::shared_ptr<ModelBridge::DataInterface>& data)
{
    beginResetModel();

    m_data = std::move(data->getLayerOutput(m_layer));

    endResetModel();
}

void DenseNodesListModel::clearRunData()
{
    beginResetModel();

    m_data.clear();

    endResetModel();
}

DenseLayerViewModel::DenseLayerViewModel(const std::shared_ptr<ModelBridge::DenseLayerInterface>& layer, QObject *parent)
    : LayerViewModelInterface{parent}
    , m_layer(layer)
    , m_nodes(new DenseNodesListModel(layer, this))
{

}

const ModelBridge::LayerInterface* DenseLayerViewModel::getLayerPointer() const
{
    return m_layer.get();
}

void DenseLayerViewModel::assignRunData(const std::shared_ptr<ModelBridge::DataInterface>& data)
{
    m_nodes->assignRunData(data);
}

void DenseLayerViewModel::clearRunData()
{
    m_nodes->clearRunData();
}

DenseLayerViewModel* create_dense_layer_viewmodel(const std::shared_ptr<ModelBridge::LayerInterface>& layer, QObject* parent)
{
    if (auto dense_ptr = std::dynamic_pointer_cast<ModelBridge::DenseLayerInterface>(layer)) {
        return new DenseLayerViewModel(dense_ptr, parent);
    }

    return nullptr;
}
