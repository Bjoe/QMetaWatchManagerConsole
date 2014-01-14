import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import QtQuick.Layouts 1.0
import QMetaWatchManager 1.0
//import QtBluetooth 5.2

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
            RowLayout {
                Label { text: qsTr("Serial Port") }
                ComboBox {
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
                Button {
                    text: qsTr("Send")
                    onClicked: handler.onSend();
                }
            }
        }
        /*
        GroupBox {
            RowLayout {
                Label { text: qsTr("Baudrate") }
                ComboBox {
                    id: baudrateComboBox
                }

                Label { text: qsTr("Data bits") }
                ComboBox {
                    id: dataBitsComboBox
                }
            }

            RowLayout {
                Label { text: qsTr("Flow control") }
                ComboBox {
                    id: flowControlComboBox
                }

                Label { text: qsTr("Parity") }
                ComboBox {
                    id: parityComboBox
                }
            }
        } */


        GroupBox {
            Layout.fillWidth: true
            Layout.fillHeight: true
            ColumnLayout {
                id: btLayout
                Label { id: top; text: qsTr("Bluetooth") }

                Rectangle {
                    id: busy

                    width: top.width * 0.7;
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: top.bottom;
                    height: 30;
                    radius: 5
                    color: "#1c56f3"
                    visible: btDiscoveryHandler.running

                    Text {
                        id: text
                        text: "Scanning"
                        font.bold: true
                        anchors.centerIn: parent
                    }

                    SequentialAnimation on color {
                        id: busyThrobber
                        ColorAnimation { easing.type: Easing.InOutSine; from: "#1c56f3"; to: "white"; duration: 1000; }
                        ColorAnimation { easing.type: Easing.InOutSine; to: "#1c56f3"; from: "white"; duration: 1000 }
                        loops: Animation.Infinite
                    }
                }

                //property BluetoothDiscoveryModel btModel:

                ListView {
                    id: btList
                    height: 100;

                    model: btDiscoveryHandler.model

                    delegate: Rectangle {
                        id: btItem

                        width: parent.width
                        height: bttext.height + 10
                        color: ListView.isCurrentItem ? "white" : "red"

                        //property BluetoothService btService: service


                        Text {
                            id: bttext
                            text: "Name: " + name + " RemoteAddress: " + remoteAddress + " DeviceName: " + deviceName
                        }
                    }
                }
                Layout.fillWidth: true

                RowLayout {
                    id: buttonGroup

                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20

                    Button {

                        text: qsTr("Scannen")
                        onClicked: {
                            btDiscoveryHandler.discover();
                            //btModel.running = false;
                            //btModel.running = true
                        }
                    }
                    Button {
                        text: qsTr("Connect")
                        onClicked: {
                            //var service = btListe.currentItem.btService;
                            //console.log(service);
                            //btSocket.service = service;
                            //btSocket.connected = true;
                            //btHandler.onConnectToDevice(service.deviceAddress);
                            btHandler.onConnectToDevice(btDiscoveryHandler.model, btList.currentIndex);
                        }
                    }
                    Button {
                        text: qsTr("Send")
                        onClicked: btHandler.onSend();
                    }
                    Button {
                        text: qsTr("Send Clock")
                        onClicked: btHandler.onSendClock();
                    }
                    Button {
                        text: qsTr("Send Property")
                        onClicked: btHandler.onSendProperty();
                    }
                    Button {
                        text: qsTr("Send Device Type")
                        onClicked: btHandler.onSendDeviceType();
                    }
                }
            }
        }
    }

    SerialPortHandler {
        id: handler
    }

    BluetoothPortHandler {
        id: btHandler

        onConnected: {
            console.log("Connect to Device " + message);
        }

        onDisconnected: {
            console.log("Device disconnected");
        }
    }

    BluetoothDiscoveryHandler {
        id: btDiscoveryHandler

        onErrorChanged: {
            console.log("Error " + btDiscoveryHandler.error)
        }
    }

    MetaWatchHandler {
        id: metaWatchHandler
    }

    /*
        BluetoothDiscoveryModel {
            id: btModel
            running: false
            discoveryMode: BluetoothDiscoveryModel.FullServiceDiscovery
            onDiscoveryModeChanged: console.log("Discovery mode: " + discoveryMode)
            onServiceDiscovered: {
                console.log("Found new service device Address: " + service.deviceAddress
                            + " Device Name: " + service.deviceName
                            + " Service Name: " + service.serviceName
                            + " Service Uuid: " + service.serviceUuid
                            + " Service Description: " + service.serviceDescription
                            + " Service Protocol: " + service.serviceProtocol);
            }
            onDeviceDiscovered: console.log("New device: " + device)
        }

        BluetoothSocket {
            id: btSocket

            onServiceChanged: {
                var service = btSocket.service;
                console.log("Service Changed" + service.deviceAddress
                            + " Device Name: " + service.deviceName
                            + " Service Name: " + service.serviceName
                            + " Service Uuid: " + service.serviceUuid
                            + " Service Description: " + service.serviceDescription
                            + " Service Protocol: " + service.serviceProtocol);
            }

            onConnectedChanged: {
                console.log("Connected Change: " + btSocket.connected);
            }

            onErrorChanged: {
                console.log("Error Change: " + btSocket.error);
            }

            onStateChanged: {
                console.log("State Change: " + btSocket.state);
            }

            onDataAvailable: {
                console.log("Data available: " + btSocket.stringData);
            }
        }
    */
}

