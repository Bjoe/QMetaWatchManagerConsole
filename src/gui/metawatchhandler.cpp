#include "metawatchhandler.h"

#include <QDebug>

#include "realtimeclockmessage.h"
#include "writelcdbuffermessage.h"
#include "setwidgetlistmessage.h"

namespace qmwm {
namespace gui {

MetaWatchHandler::MetaWatchHandler(QObject *parent) :
    QObject(parent)
{
    m_dispatcher.addHandler(m_deviceTypeMessage);
    m_dispatcher.addHandler(m_watchProperty);
}

void MetaWatchHandler::setDeviceTypeMessage(qmwp::DeviceTypeMessage *message)
{
    m_deviceTypeMessage = message;
    emit deviceTypeMessageChanged();
}

qmwp::DeviceTypeMessage* MetaWatchHandler::deviceTypeMessage() const
{
    return m_deviceTypeMessage;
}

void MetaWatchHandler::setWatchProperty(qmwp::WatchPropertyOperationMessage *message)
{
    m_watchProperty = message;
    emit watchPropertyChanged();
}

qmwp::WatchPropertyOperationMessage* MetaWatchHandler::watchProperty() const
{
    return m_watchProperty;
}

void MetaWatchHandler::setFullScreenProperty(qmwp::ControlFullScreenMessage *message)
{
    m_fullScreenProperty = message;
    emit fullScreenPropertyChanged();
}

qmwp::ControlFullScreenMessage *MetaWatchHandler::fullScreenProperty() const
{
    return m_fullScreenProperty;
}

void MetaWatchHandler::onConnect(QIODevice *device)
{
    m_dispatcher.initializeDevice(device);
}

void MetaWatchHandler::onSendClock()
{
    qmwp::RealTimeClockMessage message;
    m_dispatcher.send(&message);
}

void MetaWatchHandler::onSendProperty()
{
    m_dispatcher.send(m_watchProperty);
}

void MetaWatchHandler::onSendDeviceType()
{
    m_dispatcher.send(m_deviceTypeMessage);
}

void MetaWatchHandler::onSendFullScreen()
{
    m_dispatcher.send(m_fullScreenProperty);
}

void MetaWatchHandler::onSendWriteBuffer()
{
    qmwp::WriteLcdBufferMessage message;
    message.test();

    m_dispatcher.send(&message);
}

void MetaWatchHandler::onSendSetWidgetList()
{
    m_screenHandler->onSendSetWidgetList(&m_dispatcher);
}

} // namespace gui
} // namespace qmwm
