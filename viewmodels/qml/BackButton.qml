import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Fusion

Button {
    contentItem: Item {
        Image {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.right: backText.left
            fillMode: Image.PreserveAspectFit
            source: "qrc:/qt/qml/LayerViewModels/assets/leftarrow.bmp"
        }
        Text {
            id: backText
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            text: qsTr("Back")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }
    }
}
