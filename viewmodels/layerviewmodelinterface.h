#ifndef LAYERVIEWMODELINTERFACE_H
#define LAYERVIEWMODELINTERFACE_H

#include <QObject>
#include "qqmlintegration.h"
#include <LayerInterface.h>

class LayerViewModelInterface : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Abstract interface")
    Q_PROPERTY(QString layerType READ getLayerType NOTIFY layerTypeChanged FINAL)
    Q_PROPERTY(QString layerId READ getLayerId NOTIFY layerIdChanged FINAL)

public:
    explicit LayerViewModelInterface(QObject *parent = nullptr)
        : QObject{parent}
    {

    };

    virtual ~LayerViewModelInterface() {};

    QString getLayerType() const
    {
        return QString::fromStdString(getLayerPointer()->getLayerType());
    };

    QString getLayerId() const
    {
        return QString::fromStdString(getLayerPointer()->getId());
    };

    virtual void assignRunData(const std::shared_ptr<ModelBridge::DataInterface>& data) = 0;

signals:
    void layerTypeChanged();
    void layerIdChanged();

protected:
    virtual const ModelBridge::LayerInterface* getLayerPointer() const = 0;

};

#endif // LAYERVIEWMODELINTERFACE_H
