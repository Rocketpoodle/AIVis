#find_package(Qt6 6.5 REQUIRED COMPONENTS)

add_library(ANNRepresentation STATIC
        anntransformer.cpp
        annrepsourceconfig.cpp
)

target_include_directories(ANNRepresentation PUBLIC
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

target_link_libraries(ANNRepresentation
        AiRepresentationInterface
)

include(GNUInstallDirs)
install(TARGETS ANNRepresentation
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_subdirectory(test)
