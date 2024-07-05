import QtQuick
import LayerViewModels

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("AI Visualizer")

    HomeView {
        anchors.fill: parent
        aiLayerModel: aiViewModel
    }
}
