#include "watchpropertyoperationmessage.h"

#include <bitset>

#include "core/metawatchprotocol.h"

namespace qmwp {

class WatchPropertyOperationMessage::Private
{
public:
    std::bitset<8> m_option{ "00000000" };
};

WatchPropertyOperationMessage::WatchPropertyOperationMessage()
    : Message(
            [this](core::Protocol& protocol)
            {
                protocol.setType(0x30);
                protocol.setOption(m_priv->m_option.to_ulong());
            },
            [this](core::Protocol& protocol)
            {
                qint8 option = protocol.option();
                m_priv->m_option = std::bitset<8>(option);
            },
            0x31
      ),
    m_priv{ new Private }
{
}

WatchPropertyOperationMessage::~WatchPropertyOperationMessage()
{
}

void WatchPropertyOperationMessage::setClockFormat(ClockFormat format)
{
    if(format == ClockFormat::H24) {
        m_priv->m_option.set(0);
    } else {
        m_priv->m_option.reset(0);
    }
    setOperation(Operation::WRITE);
}

WatchPropertyOperationMessage::ClockFormat WatchPropertyOperationMessage::clockFormat() const
{
    ClockFormat format = ClockFormat::H12;
    if(m_priv->m_option.test(0)) {
        format = ClockFormat::H24;
    }
    return format;
}

void WatchPropertyOperationMessage::setShowSeconds(Seconds show)
{
    if(show == Seconds::ON) {
        m_priv->m_option.set(2);
    } else {
        m_priv->m_option.reset(2);
    }
    setOperation(Operation::WRITE);
}

WatchPropertyOperationMessage::Seconds WatchPropertyOperationMessage::showSeconds() const
{
    Seconds show = Seconds::OFF;
    if(m_priv->m_option.test(2)) {
        show = Seconds::ON;
    }
    return show;
}

void WatchPropertyOperationMessage::setDateFormat(DateFormat format)
{
    if(format == DateFormat::DDMM) {
        m_priv->m_option.set(1);
    } else {
        m_priv->m_option.reset(1);
    }
    setOperation(Operation::WRITE);
}

WatchPropertyOperationMessage::DateFormat WatchPropertyOperationMessage::dateFormat() const
{
    DateFormat format = DateFormat::MMDD;
    if(m_priv->m_option.test(1)) {
        format = DateFormat::DDMM;
    }
    return format;
}

void WatchPropertyOperationMessage::setShowSeparationLine(Separation show)
{
    if(show == Separation::ON) {
        m_priv->m_option.set(3);
    } else {
        m_priv->m_option.reset(3);
    }
    setOperation(Operation::WRITE);
}

WatchPropertyOperationMessage::Separation WatchPropertyOperationMessage::showSeparationLine() const
{
    Separation show = Separation::OFF;
    if(m_priv->m_option.test(3)) {
        show = Separation::ON;
    }
    return show;
}

void WatchPropertyOperationMessage::setAutoBacklight(Backlight light)
{
    if(light == Backlight::ENABLE) {
        m_priv->m_option.set(4);
    } else {
        m_priv->m_option.reset(4);
    }
    setOperation(Operation::WRITE);
}

WatchPropertyOperationMessage::Backlight WatchPropertyOperationMessage::autoBacklight() const
{
    Backlight light = Backlight::DISABLE;
    if(m_priv->m_option.test(4)) {
        light = Backlight::ENABLE;
    }
    return light;
}

void WatchPropertyOperationMessage::setOperation(Operation rw)
{
    if(rw == Operation::WRITE) {
        m_priv->m_option.set(7);
    } else {
        m_priv->m_option.reset(7);
    }
}

WatchPropertyOperationMessage::Operation WatchPropertyOperationMessage::operation() const
{
    Operation rw = Operation::READ;
    if(m_priv->m_option.test(7)) {
        rw = Operation::WRITE;
    }
    return rw;
}

} // namespace qmwp
