# find_package(Qt6 6.5 REQUIRED COMPONENTS)
add_library(ModelBridgeInterface STATIC
    src/DataInterface.h
    src/ModelInterface.h
    src/LayerInterface.h
    src/layers/denselayerinterface.h
    src/ModelLoaderInterface.h
    src/DataLoaderInterface.h
)

target_include_directories(ModelBridgeInterface PUBLIC
        src
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
set_target_properties(ModelBridgeInterface PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(ModelBridgeInterface

)

include(GNUInstallDirs)
install(TARGETS ModelBridgeInterface
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# add_subdirectory(test)
