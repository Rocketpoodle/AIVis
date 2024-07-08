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

    Flickable {
        Layout.fillWidth: true
        Layout.fillHeight: true
        contentHeight: nodeColumn.height
        Column {
            id: nodeColumn
            spacing: 10
            Repeater {
                model: layerModel.nodeListModel
                // replace with node delegate
                delegate: Rectangle {
                    height: 10
                    width: 10
                    color: ( output > 1) ?  "green" : "grey"
                }
            }
        }
    }
}
