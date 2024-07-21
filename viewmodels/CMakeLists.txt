find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Core)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_library(layerviewmodels STATIC)

qt_add_qml_module(layerviewmodels
    URI LayerViewModels
    VERSION 1.0
    QML_FILES
    qml/AIModelView.qml
    qml/LayerPreview.qml
    qml/layers/UnknownLayerPreview.qml
    qml/layers/DenseLayerPreview.qml
    qml/layers/DenseLayerView.qml
    qml/HomeView.qml
    qml/Zoomable.qml
    qml/layers/DenseLayerNodeDelegate.qml
    SOURCES
    ../common/utils.h
    qtutils.h
    layerviewmodelinterface.h
    layers/layerviewmodelregistry.h layers/layerviewmodelregistry.cpp
    layerviewregistry.h layerviewregistry.cpp
    layers/unknownlayerviewmodel.h layers/unknownlayerviewmodel.cpp
    layers/denselayerviewmodel.h layers/denselayerviewmodel.cpp
    aimodelviewmodel.h aimodelviewmodel.cpp
    zoomhelper.h zoomhelper.cpp
    RESOURCES
    assets/node.png
    assets/prelu.png
    assets/node.bmp
    assets/prelu.bmp
)

find_package(Qt6 COMPONENTS ShaderTools)

qt_add_shaders(layerviewmodels
    BATCHABLE
    PRECOMPILE
    OPTIMIZED
    PREFIX "/"
    FILES
        shaders/recolor.frag
)


target_include_directories(layerviewmodels PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/layers
    ${CMAKE_CURRENT_SOURCE_DIR}/../common
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
#set_target_properties(appAIVis PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appAIVis
#    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#    MACOSX_BUNDLE TRUE
#    WIN32_EXECUTABLE TRUE
#)

# Help cmake know that our target is C++
set_target_properties(layerviewmodels PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(layerviewmodels PUBLIC
        ModelBridgeInterface
        Qt6::Core
        Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS layerviewmodels
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# add_subdirectory(test)
