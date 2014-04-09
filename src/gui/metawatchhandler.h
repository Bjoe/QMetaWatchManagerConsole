#ifndef QMWM_GUI_METAWATCHHANDLER_H
#define QMWM_GUI_METAWATCHHANDLER_H

#include <QObject>
#include <QIODevice>

#include "metawatchscreenhandler.h"

#include "core/protocoldispatcher.h"
#include "devicetypemessage.h"
#include "watchpropertyoperationmessage.h"
#include "controlfullscreenmessage.h"

namespace qmwm {
namespace gui {

class MetaWatchHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qmwp::DeviceTypeMessage *deviceTypeMessage READ deviceTypeMessage WRITE setDeviceTypeMessage NOTIFY deviceTypeMessageChanged)
    Q_PROPERTY(qmwp::WatchPropertyOperationMessage* watchProperty READ watchProperty WRITE setWatchProperty NOTIFY watchPropertyChanged)
    Q_PROPERTY(qmwp::ControlFullScreenMessage* fullScreenProperty READ fullScreenProperty WRITE setFullScreenProperty NOTIFY fullScreenPropertyChanged)

public:
    explicit MetaWatchHandler(QObject *parent = 0);

    void setDeviceTypeMessage(qmwp::DeviceTypeMessage *message);
    qmwp::DeviceTypeMessage *deviceTypeMessage() const;

    void setWatchProperty(qmwp::WatchPropertyOperationMessage *message);
    qmwp::WatchPropertyOperationMessage *watchProperty() const;

    void setFullScreenProperty(qmwp::ControlFullScreenMessage *message);
    qmwp::ControlFullScreenMessage *fullScreenProperty() const;

signals:
    void deviceTypeMessageChanged();
    void watchPropertyChanged();
    void fullScreenPropertyChanged();

public slots:
    void onConnect(QIODevice *device);
    void onSendClock();
    void onSendProperty();
    void onSendDeviceType();
    void onSendFullScreen();
    void onSendWriteBuffer();
    void onSendSetWidgetList();

private:
    qmwp::core::ProtocolDispatcher m_dispatcher;
    qmwp::DeviceTypeMessage *m_deviceTypeMessage = new qmwp::DeviceTypeMessage(this);
    qmwp::WatchPropertyOperationMessage *m_watchProperty = new qmwp::WatchPropertyOperationMessage(this);
    qmwp::ControlFullScreenMessage *m_fullScreenProperty = new qmwp::ControlFullScreenMessage(this);
    MetaWatchScreenHandler *m_screenHandler = new MetaWatchScreenHandler(this);
};

} // namespace gui
} // namespace qmwm

#endif // QMWM_GUI_METAWATCHHANDLER_H
