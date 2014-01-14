#include "serialporthandler.h"

#include <QIODevice>
#include <QSerialPortInfo>
#include <QSerialPort>

#include <QDebug>

namespace qmwm {
namespace gui {

SerialPortHandler::SerialPortHandler(QObject *parent) :
    QObject(parent),
    m_serialPort(new QSerialPort(parent)),
    m_deviceHandler(new DeviceHandler(m_serialPort, parent)),
    m_model(new PortInfoModel(parent))
{
    connect(m_serialPort, SIGNAL(readyRead()), m_deviceHandler, SLOT(onReadyRead()));
}

PortInfoModel* SerialPortHandler::model()
{
    return m_model;
}

void SerialPortHandler::setModel(PortInfoModel *model)
{
    m_model = model;
}

void SerialPortHandler::onRefresh()
{
    delete m_model;
    m_model = new PortInfoModel();
    emit modelChanged();
}

void SerialPortHandler::onConnectPort(int index)
{
    QSerialPortInfo port = m_model->at(index);

    qDebug() << "Selected serial port " << port.systemLocation();

    m_serialPort->setPort(port);
    check([](QSerialPort* serialPort) -> bool { return serialPort->open(QIODevice::ReadWrite); });
    check([](QSerialPort* serialPort) -> bool { return serialPort->setBaudRate(QSerialPort::Baud115200); });
    check([](QSerialPort* serialPort) -> bool { return serialPort->setDataBits(QSerialPort::Data8); });
    check([](QSerialPort* serialPort) -> bool { return serialPort->setStopBits(QSerialPort::OneStop); });
    check([](QSerialPort* serialPort) -> bool { return serialPort->setParity(QSerialPort::NoParity); });
    check([](QSerialPort* serialPort) -> bool { return serialPort->setFlowControl(QSerialPort::NoFlowControl); });
}

void SerialPortHandler::onSend()
{
    m_deviceHandler->write();
}

void SerialPortHandler::check(std::function<bool(QSerialPort *)> func)
{
    bool ok = func(m_serialPort);
    if(ok == false) {
        m_serialPort->close();
        QString message = m_serialPort->errorString();
        qDebug() << "Error: " << message;
    }
}


} // namespace gui
} // namespace qmwm
