import QtQuick 2.15
import QtQuick.Shapes

Item {
    id: root
    required property real output
    required property int index
    property real fontSize: 8
    property real spacing: 2
    Image {
        id: nodeImage
        source: "qrc:/qt/qml/LayerViewModels/assets/node.png"
        property color monoColor: (output > 1) ? "#FF00FF00" : "#FF808080"
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        layer.enabled: true
        layer.effect: ShaderEffect {
            property var monoColor: Qt.vector4d(nodeImage.monoColor.r, nodeImage.monoColor.g, nodeImage.monoColor.b, nodeImage.monoColor.a)
            property var source: nodeImage
            fragmentShader: "/shaders/recolor.frag.qsb"
        }
    }
    Column {
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -root.width/4
        // spacing: root.spacing
        Text {
            text: index
            font.pixelSize: fontSize
        }
        Text {
            text: output
            font.pixelSize: fontSize
        }
    }
}
