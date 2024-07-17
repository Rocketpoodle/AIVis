import QtQuick 2.15
import QtQuick.Layouts
import LayerViewModels

Flickable {
    clip: true

    property alias zoomScale: zoomHelper.zoomScale
    default property alias zoomableItem: someItem.children

    contentHeight: someItem.height
    contentWidth: someItem.width

    RowLayout {
        id: someItem
    }

    WheelHandler {
        onWheel: (event)=> {
                     if(event.angleDelta.y > 0) {
                         zoomHelper.zoomIn()
                     }
                     else if (event.angleDelta.y < 0) {
                         zoomHelper.zoomOut()
                     }
                 }
    }

    ZoomHelper {
        id: zoomHelper
    }
}
