#ifndef ZOOMHELPER_H
#define ZOOMHELPER_H

#include <QObject>
#include <QQmlEngine>

class ZoomHelper : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(qreal zoomScale READ getZoomScale WRITE setZoomScale NOTIFY zoomScaleChanged)
    Q_PROPERTY(qreal viewWidth MEMBER m_viewWidth)
    Q_PROPERTY(qreal viewHeight MEMBER m_viewHeight)
    Q_PROPERTY(qreal zoomAdjust MEMBER m_zoomAdjust)

public:
    explicit ZoomHelper(QObject *parent = nullptr);

    qreal getZoomScale() const;
    void setZoomScale(const qreal& scale);

public slots:
    void zoomIn();
    void zoomOut();
    void resetZoom();

signals:
    void zoomScaleChanged();

private:
    qreal m_zoomScale;
    qreal m_viewWidth;
    qreal m_viewHeight;
    qreal m_zoomAdjust;
};

#endif // ZOOMHELPER_H
