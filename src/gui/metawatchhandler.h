#ifndef QMWM_GUI_METAWATCHHANDLER_H
#define QMWM_GUI_METAWATCHHANDLER_H

#include <QObject>
#include <QIODevice>

#include "core/protocoldispatcher.h"
#include "devicetypemessage.h"
#include "watchpropertyoperationmessage.h"

namespace qmwm {
namespace gui {

class MetaWatchHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qmwp::DeviceTypeMessage *deviceTypeMessage READ deviceTypeMessage WRITE setDeviceTypeMessage NOTIFY deviceTypeMessageChanged)
    Q_PROPERTY(qmwp::WatchPropertyOperationMessage* watchProperty READ watchProperty WRITE setWatchProperty NOTIFY watchPropertyChanged)
public:
    explicit MetaWatchHandler(QObject *parent = 0);

    void setDeviceTypeMessage(qmwp::DeviceTypeMessage *message);
    qmwp::DeviceTypeMessage *deviceTypeMessage() const;

    void setWatchProperty(qmwp::WatchPropertyOperationMessage *message);
    qmwp::WatchPropertyOperationMessage *watchProperty() const;

signals:
    void deviceTypeMessageChanged();
    void watchPropertyChanged();

public slots:
    void onConnect(QIODevice *device);
    void onSendClock();
    void onSendProperty();
    void onSendDeviceType();

private:
    qmwp::core::ProtocolDispatcher m_dispatcher;
    qmwp::DeviceTypeMessage *m_deviceTypeMessage = new qmwp::DeviceTypeMessage(this);
    qmwp::WatchPropertyOperationMessage *m_watchProperty = new qmwp::WatchPropertyOperationMessage();
};

} // namespace gui
} // namespace qmwm

#endif // QMWM_GUI_METAWATCHHANDLER_H
