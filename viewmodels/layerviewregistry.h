#ifndef LAYERVIEWREGISTRY_H
#define LAYERVIEWREGISTRY_H

#include <QObject>
#include <QHash>

#include "qtutils.h"

class LayerViewRegistry : public QObject
{
    Q_OBJECT
public:
    explicit LayerViewRegistry(QObject *parent = nullptr);

    Q_INVOKABLE QUrl getPreviewForLayerModel(const QString& layerType) const;
    Q_INVOKABLE void registerPreviewForLayerType(const QString& layerType, const QUrl& viewUrl);
    Q_INVOKABLE QUrl getViewForLayerModel(const QString& layerType) const;
    Q_INVOKABLE void registerViewForLayerType(const QString& layerType, const QUrl& viewUrl);

signals:
    void registryUpdated();

private:
    QHash<QString, QUrl> m_view_registry;
    QHash<QString, QUrl> m_preview_registry;
};

DEFINE_QML_SINGLETON(LayerViewRegistry, LayerViewRegistrySingleton);

#endif // LAYERVIEWREGISTRY_H
