import QtQuick 2.15
import QtQuick.Shapes

Item {
    id: root
    required property real output
    required property int index
    property real fontSize: 8
    property real spacing: 2
    Shape {
        anchors.fill: parent
        ShapePath {
            startX: root.height/2
            startY: 0
            strokeColor: "black"
            fillColor: (output > 1) ? "green" : "grey"

            PathArc {
                x: root.height/2
                y: root.height
                radiusX: root.height/2
                radiusY: root.height/2
            }
            PathArc {
                x: root.height/2
                y: 0
                radiusX: root.height/2
                radiusY: root.height/2
            }
        }
    }
    Column {
        anchors.centerIn: parent
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
