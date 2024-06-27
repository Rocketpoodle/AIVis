#include "layerviewregistry.h"
#include "qurl.h"

LayerViewRegistry::LayerViewRegistry(QObject *parent)
    : QObject{parent}
{
    // Unknown
    m_preview_registry["unknown"] = "qrc:/qt/qml/LayerViewModels/qml/layers/UnknownLayerPreview.qml";
    m_view_registry["unknown"] = "qrc:/qt/qml/LayerViewModels/qml/layers/UnknownLayerPreview.qml";
    // register default layer type views
    m_preview_registry["dense"] = "qrc:/qt/qml/LayerViewModels/qml/layers/DenseLayerPreview.qml";
    m_view_registry["dense"] = "qrc:/qt/qml/LayerViewModels/qml/layers/DenseLayerView.qml";
}
QUrl LayerViewRegistry::getPreviewForLayerModel(const QString& layerType) const
{
    return m_preview_registry.contains(layerType) ? m_preview_registry.value(layerType)
                                                  : m_preview_registry.value("unknown");
}

void LayerViewRegistry::registerPreviewForLayerType(const QString& layerType, const QUrl& viewUrl)
{
    m_preview_registry[layerType] = viewUrl;
}

QUrl LayerViewRegistry::getViewForLayerModel(const QString& layerType) const
{
    return m_view_registry.contains(layerType) ? m_view_registry.value(layerType)
                                               : m_view_registry.value("unknown");
}

void LayerViewRegistry::registerViewForLayerType(const QString& layerType, const QUrl& viewUrl)
{
    m_view_registry[layerType] = viewUrl;
}


