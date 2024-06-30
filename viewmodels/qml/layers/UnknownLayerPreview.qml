import QtQuick 2.15
import QtQuick.Layouts
import LayerViewModels

ColumnLayout {
    property UnknownLayerViewModel layerModel
    spacing: 0
    Text {
        text: layerModel.layerId
    }
    Text {
        text: layerModel.layerType
    }
}
