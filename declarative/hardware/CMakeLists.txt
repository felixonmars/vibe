include_directories(
    "${CMAKE_CURRENT_BINARY_DIR}/../../src/core"
    "${CMAKE_CURRENT_BINARY_DIR}/../../src/core/Vibe"
)

set(SOURCES
    hardwareengine.cpp
    battery.cpp
    storagedevice.cpp
    plugin.cpp
)

add_library(hardwareplugin SHARED ${SOURCES})
target_link_libraries(hardwareplugin
                      Qt5::Core
                      Qt5::Qml
                      KF5::Solid
                      Fluid::Fluid
                      Vibe::Core)

install(FILES qmldir plugins.qmltypes
    DESTINATION ${QML_INSTALL_DIR}/Vibe/Hardware)
install(TARGETS hardwareplugin
    DESTINATION ${QML_INSTALL_DIR}/Vibe/Hardware)
