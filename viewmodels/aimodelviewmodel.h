#ifndef AIMODELVIEWMODEL_H
#define AIMODELVIEWMODEL_H

#include "ModelInterface.h"
#include <QAbstractListModel>
#include <QObject>
#include <QQmlEngine>

#include "layerviewmodelregistry.h"
#include "qtutils.h"

class AIModelViewModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Can't be default constructed");
public:
    explicit AIModelViewModel(std::shared_ptr<ModelBridge::ModelInterface>& model, QObject *parent = nullptr);
    virtual ~AIModelViewModel();

    enum Roles {
        layerViewModel,
        layerId,
        layerType
    };

    /*!
     * \note  I don't think we want to assign run data for the whole model, instead
     *        let the view do it when opening detailed layer view
     */

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    ASSIGN_ROLES(Roles)

private:
    QVector<LayerViewModelInterface*> m_layers;
    std::shared_ptr<ModelBridge::ModelInterface> m_model;
};

#endif // AIMODELVIEWMODEL_H
