import QtQuick 2.15
import QtQuick.Controls
import LayerViewModels

Item {
    property AIModelViewModel aiLayerModel: null

    StackView {
        id: stackView
        anchors.fill: parent
        Component.onCompleted: stackView.push(modelViewComponent)
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
                }
            }
        }
    }
}
