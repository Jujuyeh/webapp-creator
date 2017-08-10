include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(
    Webapp_Creatorbackend_SRCS
    modules/Webapp_Creator/backend.cpp
    modules/Webapp_Creator/mytype.cpp
)

# Make the unit test files visible on qtcreator
add_custom_target(Webapp_Creatorbackend_UNITTEST_QML_FILES ALL SOURCES "tests/unit/tst_mytype.qml")

add_library(Webapp_Creatorbackend MODULE
    ${Webapp_Creatorbackend_SRCS}
)

set_target_properties(Webapp_Creatorbackend PROPERTIES
         LIBRARY_OUTPUT_DIRECTORY Webapp_Creator)

qt5_use_modules(Webapp_Creatorbackend Gui Qml Quick)

# Copy qmldir file to build dir for running in QtCreator
add_custom_target(Webapp_Creatorbackend-qmldir ALL
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/modules/Webapp_Creator/qmldir ${CMAKE_CURRENT_BINARY_DIR}/Webapp_Creator
    DEPENDS ${QMLFILES}
)

# Install plugin file
install(TARGETS Webapp_Creatorbackend DESTINATION ${QT_IMPORTS_DIR}/Webapp_Creator/)
install(FILES   modules/Webapp_Creator/qmldir DESTINATION ${QT_IMPORTS_DIR}/Webapp_Creator/)
