import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import QtQuick.Layouts 1.0
import QMetaWatchManager 1.0

ApplicationWindow {
    id: mainWindow
    title: qsTr("MetaWatch Manager")
    width: 1024
    height: 748

    menuBar: MenuBar {
        Menu {
            title: qsTr("Datei")

            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    statusBar: StatusBar {
        id: statusBar
        RowLayout {
            ProgressBar {
                id: statusBarProgress
            }
            Label {
                id: statusBarMessage
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent

        GroupBox {
            Layout.fillWidth: true
            Layout.minimumHeight: 30

            title: qsTr("Serial Connect")

            ColumnLayout {
                anchors.fill: parent

                RowLayout {

                    Label { text: qsTr("Serial Port") }
                    ComboBox {
                        Layout.minimumWidth: 150
                        id: portInfoComboBox
                        textRole: "systemLocation"
                        model: handler.model
                    }

                    Button {
                        text: qsTr("Refresh")
                        onClicked: handler.onRefresh();
                    }
                    Button {
                        text: qsTr("Connect")
                        onClicked: handler.onConnectPort(portInfoComboBox.currentIndex);
                    }
                }

                TextArea {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    id: serialOutput
                    readOnly: true
                }

                RowLayout {

                    TextField {
                        Layout.fillWidth: true
                        id: commandField
                    }

                    Button {
                        text: qsTr("Send")
                        onClicked: {
                            handler.onSend(commandField.text);
                            commandField.text = "";
                        }
                    }
                }
            }
        }

        GroupBox {
            Layout.fillWidth: true
            Layout.fillHeight: true

            title: qsTr("Bluetooth")

            ColumnLayout {
                anchors.fill: parent

                id: btLayout

                TableView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    id: btList

                    model: btDiscoveryHandler.model

                    TableViewColumn {
                        role: "name"
                        title: "Name"
                    }

                    TableViewColumn {
                        role: "deviceName"
                        title: "Device Name"
                    }

                    TableViewColumn {
                        role: "remoteAddress"
                        title: "Remote Address"
                    }
                }

                RowLayout {

                    id: buttonGroup

                    Button {
                        text: qsTr("Scannen")
                        onClicked: {
                            btDiscoveryHandler.discover();
                        }
                    }
                    Button {
                        text: qsTr("Connect")
                        onClicked: {
                            btHandler.onConnectToDevice(btDiscoveryHandler.model, btList.currentRow);
                        }
                    }
                }
            }
        }

        GroupBox {
            Layout.fillWidth: true

            title: qsTr("Watch")

            ColumnLayout {
                anchors.fill: parent

                Button {
                    text: qsTr("Send Clock")
                    onClicked: metaWatchHandler.onSendClock();
                }

                RowLayout {

                    Label { text: qsTr("Device Type")}

                    Label { text: deviceTypeObject.deviceTypeStr }

                    Button {
                        text: qsTr("Get Device Type")
                        onClicked: metaWatchHandler.onSendDeviceType();
                    }
                }

                RowLayout {
                    CheckBox {
                        id: clockFormatCheckBox
                        text: qsTr("Clock Format 24H")
                        checked: propertyObject.clockFormatChecked
                        onCheckedChanged: {
                            propertyObject.clockFormatChecked = checked;
                        }
                    }

                    CheckBox {
                        id: secondsCheckBox
                        text: qsTr("Seconds")
                        checked: propertyObject.showSecondsChecked
                        onCheckedChanged: {
                            propertyObject.showSecondsChecked = checked;
                        }
                    }

                    CheckBox {
                        id: dateFormatCheckBox
                        text: qsTr("Date format dd.mm.yyyy")
                        checked: propertyObject.dateFormatChecked
                        onCheckedChanged: {
                            propertyObject.dateFormatChecked = checked;
                        }
                    }

                    CheckBox {
                        id: separationLineCheckBox
                        text: qsTr("Seperation line")
                        checked: propertyObject.showSeparationLineChecked
                        onCheckedChanged: {
                            propertyObject.showSeparationLineChecked = checked;
                        }
                    }

                    CheckBox {
                        id: backlightCheckBox
                        text: qsTr("Backlight")
                        checked: propertyObject.autoBacklightChecked
                        onCheckedChanged: {
                            propertyObject.autoBacklightChecked = checked;
                        }
                    }

                    Button {
                        text: qsTr("Send Property")
                        onClicked: {
                            propertyObject.operation = WatchPropertyOperationMessage.WRITE;
                            metaWatchHandler.onSendProperty();
                        }
                    }
                    Button {
                        text: qsTr("Read Property")
                        onClicked: {
                            propertyObject.operation = WatchPropertyOperationMessage.READ;
                            metaWatchHandler.onSendProperty();
                        }
                    }
                }

                RowLayout {

                    Label { text: qsTr("Controll full screen")}

                    CheckBox {
                        text: "Full Screen"
                        checked: fullScreenObject.fullScreenChecked
                        onCheckedChanged: {
                            fullScreenObject.fullScreenChecked = checked;
                        }
                    }

                    Button {
                        text: qsTr("Send Full Screen")
                        onClicked: metaWatchHandler.onSendFullScreen();
                    }
                }

                Button {
                    text: qsTr("Send Write Buffer")
                    onClicked: metaWatchHandler.onSendWriteBuffer();
                }

                Button {
                    text: qsTr("Set CLocks via SetWidgetList")
                    onClicked: metaWatchHandler.onSendSetWidgetList();
                }
            }
        }
    }

    property DeviceTypeMessage deviceTypeObject: metaWatchHandler.deviceTypeMessage
    property WatchPropertyOperationMessage propertyObject: metaWatchHandler.watchProperty
    property ControlFullScreenMessage fullScreenObject: metaWatchHandler.fullScreenProperty

    SerialPortHandler {
        id: handler

        onError: {
            statusBarMessage.text = message;
        }

        onOutput: {
            serialOutput.append(data);
        }
    }

    BluetoothDiscoveryHandler {
        id: btDiscoveryHandler

        onErrorChanged: {
            statusBarMessage.text = "Error " + btDiscoveryHandler.error;
        }

        onRunningChanged: {
            if(btDiscoveryHandler.running) {
                statusBarMessage.text = "Scanning ....";
            } else {
                statusBarMessage.text = "Scanning .... Done.";
            }
        }
    }

    BluetoothPortHandler {
        id: btHandler

        onConnected: {
            metaWatchHandler.onConnect(device);
            statusBarMessage.text = "Connect to Device";
        }

        onDisconnected: {
            statusBarMessage.text = "Device disconnected";
        }

        onError: {
            statusBarMessage.text = message;
        }

        onStatusMessage: {
            statusBarMessage.text = message;
        }
    }

    MetaWatchHandler {
        id: metaWatchHandler
    }
}

