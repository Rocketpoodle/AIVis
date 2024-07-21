import QtQuick 2.15
import QtQuick.Controls
import LayerViewModels

Item {
    property AIModelViewModel aiLayerModel: null

    StackView {
        id: headerStackView
        height: 100
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        Component.onCompleted: headerStackView.push(homeHeaderComponent)

        popEnter: null
        popExit: null
        pushEnter: null
        pushExit: null
    }

    Component {
        id: homeHeaderComponent
        Text {
            text: qsTr("Home Model View")
        }
    }

    Component {
        id: layerHeaderComponent
        Item {
            BackButton {
                id: backButton
                Connections {
                    target: backButton
                    function onClicked() {
                        if (stackView.depth > 1) {
                            stackView.pop()
                        }
                        if (headerStackView.depth > 1) {
                            headerStackView.pop()
                        }
                    }
                }
            }
        }
    }

    StackView {
        id: stackView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: headerStackView.bottom
        anchors.bottom: parent.bottom
        Component.onCompleted: stackView.push(modelViewComponent)

        popEnter: null
        popExit: null
        pushEnter: null
        pushExit: null
    }

    Component {
        id: modelViewComponent
        AIModelView {
            id: aiModelView
            layerModel: aiLayerModel
            Connections {
                function onItemClicked(clickedLayerModel: LayerViewModelInterface) {
                    stackView.push(LayerViewRegistrySingleton.getViewForLayerModel(clickedLayerModel.layerType),
                                   {"layerModel": clickedLayerModel})
                    headerStackView.push(layerHeaderComponent)
                }
            }
        }
    }
}
