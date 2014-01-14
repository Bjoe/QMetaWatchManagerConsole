
set(QT_SRCS
    core/devicehandler.cpp
    core/metawatchprotocol.cpp
    core/metawatchmessage.cpp
    core/protocoldispatcher.cpp

    devicetypemessage.cpp
    realtimeclockmessage.cpp
    watchpropertyoperationmessage.cpp

    gui/mainwindowcontroller.cpp
    gui/serialporthandler.cpp
    gui/portinfomodel.cpp
    gui/bluetoothporthandler.cpp
    gui/bluetoothdiscoverymodel.cpp
    gui/bluetoothdiscoveryhandler.cpp
    gui/metawatchhandler.cpp
)

set(RESOURCES ../resources.qrc)

set(QML_PATH "${PROJECT_SOURCE_DIR}/assets/main.qml")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/config.h"
  )

add_library(qmwmcore STATIC ${QT_SRCS})
target_link_libraries(qmwmcore Qt5::Bluetooth Qt5::SerialPort Qt5::Widgets Qt5::Qml)

qt5_add_resources(QRC ${RESOURCES})
add_executable(qmwm main.cpp ${QRC})
target_link_libraries(qmwm qmwmcore Qt5::Core Qt5::Widgets Qt5::Qml Qt5::Quick)
