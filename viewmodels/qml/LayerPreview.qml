import QtQuick 2.15
import LayerViewModels

Item {
    id: root

    required property LayerViewModelInterface layerModel

    Loader {
        id: previewLoader

        anchors.fill: parent

        source: LayerViewRegistrySingleton.getPreviewForLayerModel(layerModel.layerType)

        Connections {
            function onLoaded() {
                if(previewLoader.item) {
                    previewLoader.item.layerModel = root.layerModel
                }
            }
        }
    }
}
