#ifndef QMWM_GUI_BLUETOOTHPORTHANDLER_H
#define QMWM_GUI_BLUETOOTHPORTHANDLER_H

#include <QObject>
#include <QVariant>
#include <QString>
#include <QtBluetooth/QBluetoothAddress>
#include <QtBluetooth/QBluetoothServiceInfo>
#include <QtBluetooth/QBluetoothSocket>
#include <QtBluetooth/QBluetoothLocalDevice>

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
    void connected(QIODevice* device);
    void disconnected();
    void error(QString message);
    void statusMessage(QString message);

public slots:
    void onConnectToDevice(BluetoothDiscoveryModel* model, int row);

private slots:
    void onConnected();
    void onError(QBluetoothSocket::SocketError socketError);
    void onState(QBluetoothSocket::SocketState state);
    void onPairingFinished(const QBluetoothAddress& address, QBluetoothLocalDevice::Pairing pairing);
    void onPairingDisplayConfirmation(const QBluetoothAddress& address, QString pin);
    void onPairingError(QBluetoothLocalDevice::Error deviceError);

private:
    QBluetoothLocalDevice* m_localDevice{new QBluetoothLocalDevice(this)};
    QBluetoothSocket* m_socket{nullptr};
};

} // namespace gui
} // namespace qmwm

#endif // QMWM_GUI_BLUETOOTHPORTHANDLER_H
