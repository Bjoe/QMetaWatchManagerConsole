#ifndef QMWP_DEVICETYPEMESSAGE_H
#define QMWP_DEVICETYPEMESSAGE_H

#include <memory>
#include <QObject>

#include "core/metawatchmessage.h"

namespace qmwp {

class DeviceTypeMessage : public QObject, public core::Message
{
    Q_OBJECT
    Q_ENUMS(qmwp::DeviceTypeMessage::Type)
    Q_PROPERTY(qmwp::DeviceTypeMessage::Type deviceType READ deviceType WRITE setDeviceType NOTIFY deviceTypeChanged)

public:
    enum class Type { RESERVED,
                      ANALOG_WATCH,
                      DIGITAL_WATCH_GEN1,
                      DIGITAL_DEVBOARD_GEN1,
                      ANALOG_DEVBOARD,
                      DIGITAL_WATCH_GEN2,
                      DIGITAL_DEVBOARD_GEN2
                    };

    DeviceTypeMessage(QObject *parent = nullptr);
    virtual ~DeviceTypeMessage();

    void setDeviceType(Type type);
    Type deviceType() const;

signals:
    void deviceTypeChanged();

private:
    class Private;
    std::unique_ptr<Private> m_priv;
};

} // namespace qmwp

#endif // QMWP_DEVICETYPEMESSAGE_H
