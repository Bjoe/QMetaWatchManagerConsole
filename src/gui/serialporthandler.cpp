#include "serialporthandler.h"

#include <QByteArray>
#include <QRegExp>
#include <QIODevice>
#include <QSerialPortInfo>
#include <QSerialPort>

#include <QDebug>

namespace qmwm {
namespace gui {

SerialPortHandler::SerialPortHandler(QObject *parent) :
    QObject(parent),
    m_serialPort(new QSerialPort(parent)),
    m_model(new PortInfoModel(parent))
{
    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortHandler::onReadyRead);
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

void SerialPortHandler::onSend(const QString& command)
{
    QByteArray bytes;
    bytes.append(command + "\r");
    m_serialPort->write(bytes);
}

void SerialPortHandler::onReadyRead()
{
    while(m_serialPort->canReadLine()) {
        QByteArray bytes = m_serialPort->readLine();
        QString data = QString(bytes.data()).simplified();
        emit output(data);
    }
}

void SerialPortHandler::check(std::function<bool(QSerialPort *)> func)
{
    bool ok = func(m_serialPort);
    if(ok == false) {
        m_serialPort->close();
        QString message = m_serialPort->errorString();
        qDebug() << "Serial Error: " << message;
        emit error(QString("Serial Error: %1").arg(message));
    }
}


} // namespace gui
} // namespace qmwm
