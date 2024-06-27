import QtQuick 2.15
import LayerViewModels

Item {
    property LayerViewModelInterface layerModel
    Text {
        anchors.horizontalCenter: parent
        anchors.top: parent.top
        text: layerModel.layerId
    }
    Text {
        anchors.horizontalCenter: parent
        anchors.top: parent.bottom
        text: layerModel.layerId
    }
}
