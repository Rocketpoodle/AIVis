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
}
