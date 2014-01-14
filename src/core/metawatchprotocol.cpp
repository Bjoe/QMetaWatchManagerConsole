#include "metawatchprotocol.h"

#include <utility>

#include <boost/crc.hpp>
#include <boost/cstdint.hpp>

namespace qmwp {
namespace core {

class Protocol::Private
{
public:
    QByteArray m_payload {};
    QString m_error = "";
    quint8 m_type = 0x00;
    quint8 m_option = 0x00;
    bool m_valid = false;
};

Protocol::Protocol()
    : m_priv{new Private}
{
}

Protocol::~Protocol()
{
}

Protocol::Protocol(const Protocol &copy)
    : m_priv{new Private}
{
    m_priv->m_payload = copy.m_priv->m_payload;
    m_priv->m_error = copy.m_priv->m_error;
    m_priv->m_type = copy.m_priv->m_type;
    m_priv->m_option = copy.m_priv->m_option;
    m_priv->m_valid = copy.m_priv->m_valid;
}

Protocol &Protocol::operator=(const Protocol &other)
{
    if(&other == this) {
        return *this;
    }
    m_priv->m_payload = other.m_priv->m_payload;
    m_priv->m_error = other.m_priv->m_error;
    m_priv->m_type = other.m_priv->m_type;
    m_priv->m_option = other.m_priv->m_option;
    m_priv->m_valid = other.m_priv->m_valid;
    return *this;
}

bool Protocol::isValid() const
{
    return m_priv->m_valid;
}

QString Protocol::lastError() const
{
    return m_priv->m_error;
}

quint8 Protocol::type() const
{
    return m_priv->m_type;
}

void Protocol::setType(quint8 type)
{
    m_priv->m_type = type;
}

quint8 Protocol::option() const
{
    return m_priv->m_option;
}

void Protocol::setOption(quint8 option)
{
    m_priv->m_option = option;
}

QByteArray Protocol::payload() const
{
    return m_priv->m_payload;
}

void Protocol::setPayload(const QByteArray &payload)
{
    m_priv->m_payload = payload;
}

QByteArray Protocol::createMessage() const
{
    int length = m_priv->m_payload.size() + 6;

    QByteArray message;
    message.resize(4);
    message[0] = 0x01;
    message[1] = length;
    message[2] = m_priv->m_type;
    message[3] = m_priv->m_option;

    message.append(m_priv->m_payload);

    boost::crc_basic<16>  crc_ccitt( 0x1021, 0xFFFF, 0, true, false );
    crc_ccitt.process_bytes( message.constData(), length - 2 );
    quint16 crc = crc_ccitt.checksum();

    message.append(crc % 256);
    message.append(crc / 256);

    return message;
}

Protocol Protocol::createProtocol(const QByteArray& message)
{
    Protocol protocol;

    if(message.at(0) != 0x01) {
        protocol.m_priv->m_valid = false;
        protocol.m_priv->m_error = QString("Wrong frame");
        return protocol;
    }

    int length = message.at(1);
    if(message.size() != length) {
        protocol.m_priv->m_valid = false;
        protocol.m_priv->m_error = QString("Wrong frame lenght");
        return protocol;
    }

    boost::crc_basic<16>  crc_ccitt( 0x1021, 0xFFFF, 0, true, false );
    crc_ccitt.process_bytes( message.constData(), length - 2 );
    quint16 crc = crc_ccitt.checksum();

    if((message.at(length-2) != static_cast<char>(crc % 256)) ||
            (message.at(length-1) != static_cast<char>(crc / 256))) {
        protocol.m_priv->m_valid = false;
        protocol.m_priv->m_error = QString("Checksum ERROR");
        return protocol;
    }

    protocol.m_priv->m_type = message.at(2);
    protocol.m_priv->m_option = message.at(3);

    if(length > 6) {
        for(int x = 4, y = 0; x < (length - 2); ++y, ++x) {
            protocol.m_priv->m_payload[y] = message.at(x);
        }
    }

    protocol.m_priv->m_valid = true;
    protocol.m_priv->m_error = QString("");
    return protocol;
}

} // namespace core
} // namespace qmwp
