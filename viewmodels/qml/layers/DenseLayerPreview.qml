import QtQuick 2.15

Item {
    property DenseLayerViewModel layerModel
    Text {
        anchors.horizontalCenter: parent
        anchors.top: parent.top
        text: layerModel.layerId
        font.bold: true
    }
    Text {
        anchors.horizontalCenter: parent
        anchors.top: parent.bottom
        text: layerModel.layerId
        font.bold: true
    }
}
