find_package(Qt6 6.5 REQUIRED COMPONENTS Core Quick)

qt_standard_project_setup(REQUIRES 6.5)

# TODO: Remove this eventually once we aren't forcing the test data
configure_file(
    ${PROJECT_SOURCE_DIR}/test/data/simple_image_classifier.json
    ${CMAKE_CURRENT_BINARY_DIR}/simple_image_classifier.json
    COPYONLY
)

configure_file(
    ${PROJECT_SOURCE_DIR}/test/data/fashion-mnist_test.csv
    ${CMAKE_CURRENT_BINARY_DIR}/fashion-mnist_test.csv
    COPYONLY
)

qt_add_executable(appAIVis
    main.cpp
    src/loader.h src/loader.cpp
)

qt_add_qml_module(appAIVis
    URI AIVis
    VERSION 1.0
    IMPORTS
    LayerViewModels
    QML_FILES Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appAIVis PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appAIVis
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appAIVis
    PRIVATE
    Qt6::Quick
    layerviewmodels
    layerviewmodelsplugin
    fdeepbridge
)

include(GNUInstallDirs)
install(TARGETS appAIVis
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
