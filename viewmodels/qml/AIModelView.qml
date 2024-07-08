import QtQuick 2.15
import QtQuick.Layouts
import LayerViewModels

RowLayout {
    id: root

    property alias layerModel: layerPreviewRepeater.model

    signal itemClicked(clickedLayerModel: LayerViewModelInterface)

    Repeater {
        id: layerPreviewRepeater
        delegate: LayerPreview {
            id: previewDelegate
            required property int index

            Layout.preferredHeight: 400
            Layout.preferredWidth: 200

            Layout.fillHeight: true

            MouseArea {
                anchors.fill: parent

                Connections {
                    function onClicked() {
                        root.itemClicked(previewDelegate.layerViewModel)
                    }
                }
            }
        }
    }
}
