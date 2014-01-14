#ifndef QMWM_DEVICEHANDLER_H
#define QMWM_DEVICEHANDLER_H

#include <QObject>
#include <QIODevice>

#include "core/metawatchmessage.h"

namespace qmwm {

class DeviceHandler : public QObject
{
    Q_OBJECT
public:
    DeviceHandler(QObject *parent = 0);
    explicit DeviceHandler(QIODevice *device, QObject *parent = 0);

    void setDevice(QIODevice *device);

    void send(const qmwp::core::Message &message);
    void write();
signals:

public slots:
    void onReadyRead();

private:
    QIODevice *m_device = nullptr;
};

} // namespace qmwm

#endif // QMWM_DEVICEHANDLER_H
