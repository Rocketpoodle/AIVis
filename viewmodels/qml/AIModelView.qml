import QtQuick 2.15
import QtQuick.Layouts

RowLayout {
    id: root

    property alias layerModel: layerPreviewRepeater.model

    Repeater {
        id: layerPreviewRepeater
        delegate: LayerPreview {
            Layout.fillHeight: true

        }
    }
}
