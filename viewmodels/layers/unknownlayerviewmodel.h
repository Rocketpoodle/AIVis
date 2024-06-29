#ifndef UNKNOWNLAYERVIEWMODEL_H
#define UNKNOWNLAYERVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <layerviewmodelinterface.h>

class UnknownLayerViewModel : public LayerViewModelInterface
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Can't be default constructed");
public:
    explicit UnknownLayerViewModel(const std::shared_ptr<ModelBridge::LayerInterface>& layer, QObject *parent = nullptr);
    virtual ~UnknownLayerViewModel() {};

    virtual void assignRunData(const std::shared_ptr<ModelBridge::DataInterface>& data) override {};

protected:
    virtual const ModelBridge::LayerInterface* getLayerPointer() const override { return m_layer.get(); };

private:
    std::shared_ptr<ModelBridge::LayerInterface> m_layer;

};

UnknownLayerViewModel* create_unknown_layer_viewmodel(const std::shared_ptr<ModelBridge::LayerInterface>& layer, QObject* parent);

#endif // UNKNOWNLAYERVIEWMODEL_H
