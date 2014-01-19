#include "devicetypemessage.h"

#include <QByteArray>

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
                //quint8 option = protocol.option(); Doku MetaWatch Remote Message Protocol V2.0.5 is wrong
                QByteArray byte = protocol.payload();
                quint8 option = static_cast<quint8>(byte.at(0));
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

QString DeviceTypeMessage::deviceTypeStr() const
{
    QString type
            ;
    switch(m_priv->m_type) {
    case Type::ANALOG_DEVBOARD:
        type = "Analog devboard";
        break;
    case Type::ANALOG_WATCH:
        type = "Analog watch";
        break;
    case Type::DIGITAL_DEVBOARD_GEN1:
        type = "Digital devboard Gen1";
        break;
    case Type::DIGITAL_DEVBOARD_GEN2:
        type = "Digital devboard Gen2";
        break;
    case Type::DIGITAL_WATCH_GEN1:
        type = "Digital watch Gen1";
        break;
    case Type::DIGITAL_WATCH_GEN2:
        type = "Digital watch Gen2";
        break;
    default:
        type = "RESEVERD";
    }
    return type;
}

} // namespace qmwp
