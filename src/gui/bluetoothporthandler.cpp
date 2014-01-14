#include "bluetoothporthandler.h"

#include <QtBluetooth/QBluetoothUuid>

#include <QDebug>

#include "realtimeclockmessage.h"
#include "devicetypemessage.h"
#include "watchpropertyoperationmessage.h"

namespace qmwm {
namespace gui {

BluetoothPortHandler::BluetoothPortHandler(QObject *parent) :
    QObject(parent), m_localDevice{new QBluetoothLocalDevice(parent)}, m_socket{nullptr}, m_deviceHandler{nullptr}
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
    if(m_deviceHandler) {
        delete m_deviceHandler;
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

    m_deviceHandler = new DeviceHandler(m_socket, this);
    connect(m_socket, SIGNAL(readyRead()), m_deviceHandler, SLOT(onReadyRead()));

    m_socket->connectToService(*service);
}

void BluetoothPortHandler::onSend()
{
    if(m_deviceHandler) {
        m_deviceHandler->write();
    }
}

void BluetoothPortHandler::onSendClock()
{
    if(m_deviceHandler) {
        qmwp::RealTimeClockMessage message;
        m_deviceHandler->send(message);
    }
}

void BluetoothPortHandler::onSendProperty()
{
    if(m_deviceHandler) {
        qmwp::WatchPropertyOperationMessage message;
        message.setClockFormat(qmwp::WatchPropertyOperationMessage::ClockFormat::H24);
        message.setDateFormat(qmwp::WatchPropertyOperationMessage::DateFormat::DDMM);
        m_deviceHandler->send(message);
    }
}

void BluetoothPortHandler::onSendDeviceType()
{
    if(m_deviceHandler) {
        qmwp::DeviceTypeMessage message;
        m_deviceHandler->send(message);
    }
}

void BluetoothPortHandler::onError(QBluetoothSocket::SocketError error)
{
    qDebug() << "Error: " << error;
}

void BluetoothPortHandler::onState(QBluetoothSocket::SocketState state)
{
    qDebug() << "State: " << state;
}

void BluetoothPortHandler::onPairingFinished(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing)
{
    qDebug() << "Pairing: " << pairing;

}

void BluetoothPortHandler::onPairingDisplayConfirmation(const QBluetoothAddress &address, QString pin)
{
    qDebug() << " Device Address: " << address.toString() << " PIN: " << pin;
    m_localDevice->pairingConfirmation(true);
}

void BluetoothPortHandler::onPairingError(QBluetoothLocalDevice::Error error)
{
    qDebug() << "Error: " << error;
}

void BluetoothPortHandler::onConnected()
{
    emit connected(m_socket->peerName());
}

} // namespace gui
} // namespace qmwm
