#include "devicetypemessage.h"

namespace qmwp {

class DeviceTypeMessage::Private
{
public:
    Type m_type = Type::RESERVED;
};

DeviceTypeMessage::DeviceTypeMessage(QObject *parent)
    : QObject(parent), Message(
          [] (core::Protocol& protocol) {
                protocol.setType(0x01);
            },
            [this] (core::Protocol& protocol) {
                quint8 option = protocol.option();
                setDeviceType(Type(option));
            },
            0x02
        ),
    m_priv{ new Private }
{}

DeviceTypeMessage::~DeviceTypeMessage()
{
}

void DeviceTypeMessage::setDeviceType(DeviceTypeMessage::Type type)
{
    m_priv->m_type = type;
    emit deviceTypeChanged();
}

DeviceTypeMessage::Type DeviceTypeMessage::deviceType() const
{
    return m_priv->m_type;
}

} // namespace qmwp
