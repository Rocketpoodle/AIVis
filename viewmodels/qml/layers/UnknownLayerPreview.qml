import QtQuick 2.15
import LayerViewModels

Item {
    property UnknownLayerViewModel layerModel
    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: layerModel.layerId
    }
    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.bottom
        text: layerModel.layerType
    }
}
