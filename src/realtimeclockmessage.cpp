#include "realtimeclockmessage.h"

#include <QByteArray>

#include "core/metawatchprotocol.h"

namespace qmwp {

class RealTimeClockMessage::Private
{
public:
    QByteArray createPayload()
    {
        QByteArray payload;
        payload.append(m_year / 256);
        payload.append(m_year % 256);
        payload.append(m_month);
        payload.append(m_day);
        payload.append(m_dayOfWeek);
        payload.append(m_hour);
        payload.append(m_minute);
        payload.append(m_second);
        return payload;
    }

    int m_year;
    int m_month;
    int m_day;
    int m_dayOfWeek;
    int m_hour;
    int m_minute;
    int m_second;
};

RealTimeClockMessage::RealTimeClockMessage()
    : Message(
            [this] (core::Protocol& protocol)
            {
                protocol.setType(0x26);
                protocol.setPayload(m_priv->createPayload());
            },
            [] (core::Protocol& protocol) {},
            0x26
     ),
    m_priv{ new Private }
{
    setDateTime(QDateTime::currentDateTime());
}

RealTimeClockMessage::~RealTimeClockMessage()
{
}

void RealTimeClockMessage::setDateTime(const QDateTime dateTime)
{
    setDate(dateTime.date());
    setTime(dateTime.time());
}

void RealTimeClockMessage::setDate(const QDate date)
{
    m_priv->m_year = date.year();
    m_priv->m_month = date.month();
    m_priv->m_day = date.day();
    m_priv->m_dayOfWeek = date.dayOfWeek();
}

void RealTimeClockMessage::setTime(const QTime time)
{
    m_priv->m_hour = time.hour();
    m_priv->m_minute = time.minute();
    m_priv->m_second = time.second();
}

void RealTimeClockMessage::setYear(int year)
{
    m_priv->m_year = year;
}

void RealTimeClockMessage::setMonth(int month)
{
    m_priv->m_month = month;
}

void RealTimeClockMessage::setDay(int day)
{
    m_priv->m_day = day;
}

void RealTimeClockMessage::septDayOfWeek(int dayOfWeek)
{
    m_priv->m_dayOfWeek = dayOfWeek;
}

void RealTimeClockMessage::setHour(int hour)
{
    m_priv->m_hour = hour;
}

void RealTimeClockMessage::setMinute(int minute)
{
    m_priv->m_minute = minute;
}

void RealTimeClockMessage::setSecond(int second)
{
    m_priv->m_second = second;
}

} // namespace qmwp
