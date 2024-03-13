find_package(Qt6 6.5 REQUIRED COMPONENTS)

qt_standard_project_setup(REQUIRES 6.5)

add_library(AiRepresentationInterface STATIC
    src/abstractairepresentation.cpp
    src/abstractaifactory.cpp
    src/abstractaitransformer.cpp

)

target_include_directories(AiRepresentationInterface PUBLIC
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

target_link_libraries(AiRepresentationInterface

)

include(GNUInstallDirs)
install(TARGETS AiRepresentationInterface
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_subdirectory(test)
