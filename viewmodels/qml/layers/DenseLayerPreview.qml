import QtQuick 2.15
import LayerViewModels

Item {
    property DenseLayerViewModel layerModel
    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: layerModel.layerId
        font.bold: true
    }
    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.bottom
        text: layerModel.layerType
        font.bold: true
    }
}
