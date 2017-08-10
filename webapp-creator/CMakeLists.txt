project(webapp-creator C CXX)
cmake_minimum_required(VERSION 2.8.9)

# Do not remove this line, its required for the correct functionality of the Ubuntu-SDK
set(UBUNTU_MANIFEST_PATH "manifest.json.in" CACHE INTERNAL "Tells QtCreator location and name of the manifest file")
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Qt5Core)
find_package(Qt5Qml)
find_package(Qt5Quick)
# find_package(ubuntu-sdk-libs)

# Automatically create moc files
set(CMAKE_AUTOMOC ON)

# Components PATH
execute_process(
    COMMAND dpkg-architecture -qDEB_HOST_MULTIARCH
    OUTPUT_VARIABLE ARCH_TRIPLET
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(QT_IMPORTS_DIR "lib/${ARCH_TRIPLET}")

option(INSTALL_TESTS "Install the tests on make install" on)

set(APP_NAME          webapp-creator)
set(APP_ID            "webapp-creator.jujuyeh")
set(WEBAPP-CREATOR_DIR "share/qml/webapp-creator")
set(MAIN_QML          "Main.qml")
set(ICON              "graphics/webapp-creator.svg")

# Set install paths
set(CMAKE_INSTALL_PREFIX /)
set(DATA_DIR /)
set(DESKTOP_DIR ${DATA_DIR})
set(DESKTOP_FILE_NAME "webapp-creator.desktop")

set(EXEC "qmlscene %U ${WEBAPP-CREATOR_DIR}/${MAIN_QML}")

# This command figures out the target architecture for use in the manifest file
execute_process(
  COMMAND dpkg-architecture -qDEB_HOST_ARCH
  OUTPUT_VARIABLE CLICK_ARCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

configure_file(manifest.json.in ${CMAKE_CURRENT_BINARY_DIR}/manifest.json)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/manifest.json
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(DIRECTORY "app/graphics" DESTINATION ${DATA_DIR})
install(DIRECTORY "app/extras" DESTINATION ${DATA_DIR})
install(FILES "webapp-creator.apparmor" DESTINATION ${DATA_DIR})
install(FILES "wac-contenthub.json" DESTINATION ${DATA_DIR})
install(FILES "app/placeholder-app-icon.svg" DESTINATION ${WEBAPP-CREATOR_DIR})
install(FILES "app/graphics/ci.svg" DESTINATION ${WEBAPP-CREATOR_DIR})
install(FILES "app/graphics/ju.svg" DESTINATION ${WEBAPP-CREATOR_DIR})

add_subdirectory(app)
add_subdirectory(backend)
add_subdirectory(po)

add_custom_target("autopilot" chmod +x ${CMAKE_SOURCE_DIR}/app/tests/autopilot/run
                    COMMAND ${CMAKE_SOURCE_DIR}/app/tests/autopilot/run
                    DEPENDS Webapp_Creatorbackend Webapp_Creatorbackend-qmldir
                    WORKING_DIRECTORY ./app)

add_custom_target("check"
                    COMMAND /usr/bin/qmltestrunner -input ${CMAKE_SOURCE_DIR}/backend/tests/unit -import ${CMAKE_BINARY_DIR}/backend
                    COMMAND /usr/bin/qmltestrunner -input ${CMAKE_SOURCE_DIR}/app/tests/unit -import ${CMAKE_BINARY_DIR}/backend
                    DEPENDS Webapp_Creatorbackend Webapp_Creatorbackend-qmldir
                    WORKING_DIRECTORY ./app)

add_custom_target("run" /usr/bin/qmlscene -I ${CMAKE_BINARY_DIR}/backend  ${CMAKE_SOURCE_DIR}/app/Main.qml
                    DEPENDS Webapp_Creatorbackend Webapp_Creatorbackend-qmldir
                    WORKING_DIRECTORY ./app)

# No op custom target for all not compiled files, so they show up in the QtCreator project tree
add_custom_target("webapp-creator_ClickFiles" ALL SOURCES "webapp-creator.apparmor" "manifest.json.in")
