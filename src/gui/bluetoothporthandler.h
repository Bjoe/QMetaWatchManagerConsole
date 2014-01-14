#ifndef QMWM_GUI_BLUETOOTHPORTHANDLER_H
#define QMWM_GUI_BLUETOOTHPORTHANDLER_H

#include <QObject>
#include <QVariant>
#include <QString>
#include <QtBluetooth/QBluetoothAddress>
#include <QtBluetooth/QBluetoothServiceInfo>
#include <QtBluetooth/QBluetoothSocket>
#include <QtBluetooth/QBluetoothLocalDevice>

#include "core/devicehandler.h"
#include "gui/bluetoothdiscoverymodel.h"

namespace qmwm {
namespace gui {

class BluetoothPortHandler : public QObject
{
    Q_OBJECT
public:
    explicit BluetoothPortHandler(QObject *parent = 0);
    ~BluetoothPortHandler();

signals:
    void connected(const QString &message);
    void disconnected();

public slots:
    void onConnectToDevice(BluetoothDiscoveryModel* model, int row);
    void onSend();
    void onSendClock();
    void onSendProperty();
    void onSendDeviceType();

private slots:
    void onConnected();
    void onError(QBluetoothSocket::SocketError error);
    void onState(QBluetoothSocket::SocketState state);
    void onPairingFinished(const QBluetoothAddress& address, QBluetoothLocalDevice::Pairing pairing);
    void onPairingDisplayConfirmation(const QBluetoothAddress& address, QString pin);
    void onPairingError(QBluetoothLocalDevice::Error error);

private:
    QBluetoothLocalDevice* m_localDevice;
    QBluetoothSocket* m_socket;
    DeviceHandler* m_deviceHandler;
};

} // namespace gui
} // namespace qmwm

#endif // QMWM_GUI_BLUETOOTHPORTHANDLER_H
