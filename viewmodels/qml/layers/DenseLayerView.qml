import QtQuick 2.15
import QtQuick.Layouts
import LayerViewModels

ColumnLayout {
    property DenseLayerViewModel layerModel
    spacing: 0
    Text {
        text: "Dense Full View"
    }
    Text {
        text: layerModel.layerId
        font.bold: true
    }
    Text {
        text: layerModel.layerType
        font.bold: true
    }

    Zoomable {
        Layout.fillWidth: true
        Layout.fillHeight: true
        id: zoomable
        zoomableItem: Column {
            id: nodeColumn
            spacing: 20 * zoomable.zoomScale
            Repeater {
                id: nodeRepeater
                model: layerModel.nodeListModel
                delegate: DenseLayerNodeDelegate {
                    height: 100* zoomable.zoomScale
                    width: 100* zoomable.zoomScale
                    fontSize: 12 * zoomable.zoomScale
                    spacing: 2 * zoomable.zoomScale
                }
            }
        }
    }
}
