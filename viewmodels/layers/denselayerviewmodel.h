#ifndef DENSELAYERVIEWMODEL_H
#define DENSELAYERVIEWMODEL_H

#include <QObject>
#include "qqmlintegration.h"
#include "DataInterface.h"
#include "layers/denselayerinterface.h"
#include "layerviewmodelinterface.h"
#include "qabstractitemmodel.h"
#include "qtutils.h"

class DenseNodesListModel: public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Can't be default constructed")
public:
    enum Roles {
        output
    };

    explicit DenseNodesListModel(const std::shared_ptr<ModelBridge::DenseLayerInterface>& layer, QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    void assignRunData(const std::shared_ptr<ModelBridge::DataInterface>& data);

    void clearRunData();

    ASSIGN_ROLES(Roles)

private:
    std::shared_ptr<ModelBridge::DenseLayerInterface> m_layer;

    std::vector<double> m_data;
};

class DenseLayerViewModel : public LayerViewModelInterface
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Can't be default constructed")
    Q_PROPERTY(DenseNodesListModel* nodeListModel READ getNodesListModel NOTIFY nodesListModelChanged)

public:
    explicit DenseLayerViewModel(const std::shared_ptr<ModelBridge::DenseLayerInterface>& layer, QObject *parent = nullptr);
    virtual ~DenseLayerViewModel() {};

    virtual void assignRunData(const std::shared_ptr<ModelBridge::DataInterface>& data) override;

    virtual void clearRunData() override;

    DenseNodesListModel* getNodesListModel() { return m_nodes; }

signals:
    void nodesListModelChanged();

protected:
    virtual const ModelBridge::LayerInterface* getLayerPointer() const override;

private:
    std::shared_ptr<ModelBridge::DenseLayerInterface> m_layer;

    DenseNodesListModel* m_nodes;
};

DenseLayerViewModel* create_dense_layer_viewmodel(const std::shared_ptr<ModelBridge::LayerInterface>& layer, QObject* parent);

#endif // DENSELAYERVIEWMODEL_H
