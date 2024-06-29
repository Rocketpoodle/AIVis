import QtQuick 2.15
import LayerViewModels

Item {
    id: root

    required property LayerViewModelInterface layerViewModel
    required property string layerType
    required property string layerId

    Loader {
        id: previewLoader

        anchors.fill: parent

        source: { return LayerViewRegistrySingleton.getPreviewForLayerModel(root.layerType) }

        Connections {
            function onLoaded() {
                if(previewLoader.item) {
                    previewLoader.item.layerModel = root.layerViewModel
                }
            }
        }
    }
}
