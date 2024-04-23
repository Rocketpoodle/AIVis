#find_package(Qt6 6.5 REQUIRED COMPONENTS)
find_package(frugally-deep)
find_package(eigen)

add_library(fdeepbridge STATIC
        ext_data_model.h
        ext_data_model_layer.h
        import_ext_data_model.h
        external_output_dict.h
        fdeepmodel.h fdeepmodel.cpp
        fdeeplayer.h fdeeplayer.cpp
        fdeepdata.h fdeepdata.cpp
)

target_include_directories(fdeepbridge PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
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
set_target_properties(fdeepbridge PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(fdeepbridge
        ModelBridgeInterface
        frugally-deep::fdeep
        Eigen3::Eigen
)

include(GNUInstallDirs)
install(TARGETS fdeepbridge
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_subdirectory(test)
