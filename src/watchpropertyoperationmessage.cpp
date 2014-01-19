#include "watchpropertyoperationmessage.h"

#include <QDebug>
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
                qDebug() << "Option " << protocol.option();
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
    emit clockFormatChanged();
    setOperation(Operation::WRITE);
}

WatchPropertyOperationMessage::ClockFormat WatchPropertyOperationMessage::clockFormat() const
{
    ClockFormat format = ClockFormat::H12;
    if(clockFormatChecked()) {
        format = ClockFormat::H24;
    }
    return format;
}

void WatchPropertyOperationMessage::setClockFormatChecked(bool checked)
{
    if(checked) {
        setClockFormat(ClockFormat::H24);
    } else {
        setClockFormat(ClockFormat::H12);
    }
}

bool WatchPropertyOperationMessage::clockFormatChecked() const
{
    return m_priv->m_option.test(0);
}

void WatchPropertyOperationMessage::setShowSeconds(Seconds show)
{
    if(show == Seconds::ON) {
        m_priv->m_option.set(2);
    } else {
        m_priv->m_option.reset(2);
    }
    emit showSecondsChanged();
    setOperation(Operation::WRITE);
}

WatchPropertyOperationMessage::Seconds WatchPropertyOperationMessage::showSeconds() const
{
    Seconds show = Seconds::OFF;
    if(showSecondsChecked()) {
        show = Seconds::ON;
    }
    return show;
}

void WatchPropertyOperationMessage::setShowSecondsChecked(bool checked)
{
    if(checked) {
        setShowSeconds(Seconds::ON);
    } else {
        setShowSeconds(Seconds::OFF);
    }
}

bool WatchPropertyOperationMessage::showSecondsChecked() const
{
    return m_priv->m_option.test(2);
}

void WatchPropertyOperationMessage::setDateFormat(DateFormat format)
{
    if(format == DateFormat::DDMM) {
        m_priv->m_option.set(1);
    } else {
        m_priv->m_option.reset(1);
    }
    emit dateFormatChanged();
    setOperation(Operation::WRITE);
}

WatchPropertyOperationMessage::DateFormat WatchPropertyOperationMessage::dateFormat() const
{
    DateFormat format = DateFormat::MMDD;
    if(dateFormatChecked()) {
        format = DateFormat::DDMM;
    }
    return format;
}

void WatchPropertyOperationMessage::setDateFormatChecked(bool checked)
{
    if(checked) {
        setDateFormat(DateFormat::DDMM);
    } else {
        setDateFormat(DateFormat::MMDD);
    }
}

bool WatchPropertyOperationMessage::dateFormatChecked() const
{
    return m_priv->m_option.test(1);
}

void WatchPropertyOperationMessage::setShowSeparationLine(Separation show)
{
    if(show == Separation::ON) {
        m_priv->m_option.set(3);
    } else {
        m_priv->m_option.reset(3);
    }
    emit showSeparationLineChanged();
    setOperation(Operation::WRITE);
}

WatchPropertyOperationMessage::Separation WatchPropertyOperationMessage::showSeparationLine() const
{
    Separation show = Separation::OFF;
    if(showSeparationLineChecked()) {
        show = Separation::ON;
    }
    return show;
}

void WatchPropertyOperationMessage::setShowSeparationLineChecked(bool checked)
{
    if(checked) {
        setShowSeparationLine(Separation::ON);
    } else {
        setShowSeparationLine(Separation::OFF);
    }
}

bool WatchPropertyOperationMessage::showSeparationLineChecked() const
{
    return m_priv->m_option.test(3);
}

void WatchPropertyOperationMessage::setAutoBacklight(Backlight light)
{
    if(light == Backlight::ENABLE) {
        m_priv->m_option.set(4);
    } else {
        m_priv->m_option.reset(4);
    }
    emit autoBacklightChanged();
    setOperation(Operation::WRITE);
}

WatchPropertyOperationMessage::Backlight WatchPropertyOperationMessage::autoBacklight() const
{
    Backlight light = Backlight::DISABLE;
    if(autoBacklightChecked()) {
        light = Backlight::ENABLE;
    }
    return light;
}

void WatchPropertyOperationMessage::setAutoBacklightChecked(bool checked)
{
    if(checked) {
        setAutoBacklight(Backlight::ENABLE);
    } else {
        setAutoBacklight(Backlight::DISABLE);
    }
}

bool WatchPropertyOperationMessage::autoBacklightChecked() const
{
    return m_priv->m_option.test(4);
}

void WatchPropertyOperationMessage::setOperation(Operation rw)
{
    if(rw == Operation::READ) {
        m_priv->m_option.set(7);
    } else {
        m_priv->m_option.reset(7);
    }
    emit operationChanged();
}

WatchPropertyOperationMessage::Operation WatchPropertyOperationMessage::operation() const
{
    Operation rw = Operation::WRITE;
    if(operationChecked()) {
        rw = Operation::READ;
    }
    return rw;
}

void WatchPropertyOperationMessage::setOperationChecked(bool checked)
{
    if(checked) {
        setOperation(Operation::READ);
    } else {
        setOperation(Operation::WRITE);
    }
}

bool WatchPropertyOperationMessage::operationChecked() const
{
    return m_priv->m_option.test(7);
}

} // namespace qmwp
