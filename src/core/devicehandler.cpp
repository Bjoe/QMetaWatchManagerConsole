#include "devicehandler.h"

#include <QByteArray>
#include <QTime>
#include <QDate>
#include <QDateTime>
#include <QDebug>

#include <boost/crc.hpp>
#include <boost/cstdint.hpp>

namespace qmwm {

DeviceHandler::DeviceHandler(QObject *parent) : QObject(parent)
{

}

DeviceHandler::DeviceHandler(QIODevice *device, QObject *parent) :
    QObject(parent), m_device(device)
{
}

void DeviceHandler::setDevice(QIODevice *device)
{
    m_device = device;
}

void DeviceHandler::send(const qmwp::core::Message& message)
{
    qmwp::core::Protocol protocol = message.createProtocol();
    QByteArray bytes = protocol.createMessage();
    m_device->write(bytes);
}

void DeviceHandler::write()
{
    QByteArray initFrame;
    initFrame.resize(6);
    initFrame[0] = 0x01;
    initFrame[1] = 0x06;
    initFrame[2] = 0x01;
    initFrame[3] = 0x00;

    boost::crc_basic<16>  crc_ccitt( 0x1021, 0xFFFF, 0, true, false );
    crc_ccitt.process_bytes( initFrame.constData(), initFrame.size() - 2 );
    quint16 crc1 = crc_ccitt.checksum();
    qDebug() << QString("%1").arg(crc1, 0, 16);

    initFrame[4] = crc1 % 256;
    initFrame[5] = crc1 / 256;

    m_device->write(initFrame);

    QDateTime dateTime = QDateTime::currentDateTime();
    QDate date = dateTime.date();
    QTime time = dateTime.time();

    QByteArray rtcFrame;
    rtcFrame.resize(16);
    rtcFrame[0] = 0x01;
    rtcFrame[1] = 16;
    rtcFrame[2] = 0x26;
    rtcFrame[3] = 0x00;

    int year = date.year();
    rtcFrame[4] = year / 256;
    rtcFrame[5] = year % 256;
    rtcFrame[6] = date.month();
    rtcFrame[7] = date.day();
    rtcFrame[8] = date.dayOfWeek();

    rtcFrame[9] = time.hour();
    rtcFrame[10] = time.minute();
    rtcFrame[11] = time.second();

    rtcFrame[12] = 1; // 24hr
    rtcFrame[13] = 1; // dd/mm

    boost::crc_basic<16>  crc_ccitt1( 0x1021, 0xFFFF, 0, true, false );
    crc_ccitt1.process_bytes( rtcFrame.constData(), rtcFrame.size() - 2 );
    quint16 crc = crc_ccitt1.checksum();
    qDebug() << QString("%1").arg(crc, 0, 16);

    rtcFrame[14] = crc % 256;
    rtcFrame[15] = crc / 256;

    m_device->write(rtcFrame);

    QByteArray propertyFrame;
    propertyFrame.resize(6);
    propertyFrame[0] = 0x01;
    propertyFrame[1] = 6;
    propertyFrame[2] = 0x30;
    propertyFrame[3] = 0x1F;

    boost::crc_basic<16>  crc_ccitt2( 0x1021, 0xFFFF, 0, true, false );
    crc_ccitt2.process_bytes( propertyFrame.constData(), propertyFrame.size() - 2 );
    quint16 crc2 = crc_ccitt2.checksum();
    qDebug() << QString("%1").arg(crc2, 0, 16);

    propertyFrame[4] = crc2 % 256;
    propertyFrame[5] = crc2 / 256;

    m_device->write(propertyFrame);
}

void DeviceHandler::onReadyRead()
{
    QByteArray data = m_device->readAll();
    qDebug() << "data " << QString("%1").arg(data.data(), 0, 16);
}



} // namespace qmwm
