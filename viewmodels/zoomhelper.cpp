#include "zoomhelper.h"

ZoomHelper::ZoomHelper(QObject *parent)
    : QObject{parent}
    , m_zoomScale(1)
    , m_viewWidth(1)
    , m_viewHeight(1)
    , m_zoomAdjust(0.1)
{

}

qreal ZoomHelper::getZoomScale() const
{
    return m_zoomScale;
}

void ZoomHelper::setZoomScale(const qreal& scale)
{
    if (scale <= 0.0) {
        qWarning() << "Can't set scale to 0!";
    }

    if (scale != m_zoomScale) {
        m_zoomScale = scale;
        emit zoomScaleChanged();
    }
}

void ZoomHelper::zoomIn()
{
    setZoomScale(m_zoomScale*(1.0+m_zoomAdjust));
}

void ZoomHelper::zoomOut()
{
    setZoomScale(m_zoomScale*(1.0-m_zoomAdjust));
}

void ZoomHelper::resetZoom()
{
    setZoomScale(1.0);
}
