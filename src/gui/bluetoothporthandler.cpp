#include "bluetoothporthandler.h"

#include <QtBluetooth/QBluetoothUuid>

#include <QDebug>

#include "realtimeclockmessage.h"
#include "devicetypemessage.h"
#include "watchpropertyoperationmessage.h"

namespace qmwm {
namespace gui {

BluetoothPortHandler::BluetoothPortHandler(QObject *parent) :
    QObject(parent)
{
    connect(m_localDevice, SIGNAL(pairingFinished(QBluetoothAddress,QBluetoothLocalDevice::Pairing)), SLOT(onPairingFinished(QBluetoothAddress,QBluetoothLocalDevice::Pairing)));
    connect(m_localDevice, SIGNAL(pairingDisplayConfirmation(QBluetoothAddress,QString)), SLOT(onPairingDisplayConfirmation(QBluetoothAddress,QString)));
    m_localDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverableLimitedInquiry);
}

BluetoothPortHandler::~BluetoothPortHandler()
{
    if(m_socket) {
        delete m_socket;
    }
}

void BluetoothPortHandler::onConnectToDevice(BluetoothDiscoveryModel* model, int row)
{
    if(m_socket) {
        delete m_socket;
    }
    const QBluetoothServiceInfo* service = model->get(row);

    qDebug() << "Device " << service->serviceName();

    //QBluetoothAddress bluetoothAddress(service);

    // m_localDevice->requestPairing(bluetoothAddress, QBluetoothLocalDevice::AuthorizedPaired);

    //QBluetoothUuid uuid;
    m_socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    connect(m_socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(m_socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
    connect(m_socket, SIGNAL(error(QBluetoothSocket::SocketError)), this, SLOT(onError(QBluetoothSocket::SocketError)));
    connect(m_socket, SIGNAL(stateChanged(QBluetoothSocket::SocketState)), this, SLOT(onState(QBluetoothSocket::SocketState)));

    m_socket->connectToService(*service);
}

void BluetoothPortHandler::onError(QBluetoothSocket::SocketError socketError)
{
    qDebug() << "Error: " << socketError;
    emit error(QString("Socket error: %1").arg(socketError));
}

void BluetoothPortHandler::onState(QBluetoothSocket::SocketState state)
{
    qDebug() << "State: " << state;
    emit statusMessage(QString("State : %1").arg(state));
}

void BluetoothPortHandler::onPairingFinished(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing)
{
    qDebug() << "Pairing: " << pairing;
    emit statusMessage(QString("Pairing: %1 Address: %2").arg(pairing).arg(address.toString()));
}

void BluetoothPortHandler::onPairingDisplayConfirmation(const QBluetoothAddress &address, QString pin)
{
    qDebug() << " Device Address: " << address.toString() << " PIN: " << pin;
    emit statusMessage(QString("Device Address %1 PIN: %2").arg(address.toString()).arg(pin));
    m_localDevice->pairingConfirmation(true);
}

void BluetoothPortHandler::onPairingError(QBluetoothLocalDevice::Error deviceError)
{
    qDebug() << "Error: " << deviceError;
    emit error(QString("Pairing error: %1").arg(deviceError));
}

void BluetoothPortHandler::onConnected()
{
    emit connected(m_socket);
}

} // namespace gui
} // namespace qmwm
