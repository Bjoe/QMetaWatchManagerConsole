
#include <QtTest/QtTest>
#include <QByteArray>
#include <QDate>
#include <QTime>

#include "testconfig.h"

#include "realtimeclockmessage.h"
#include "core/metawatchprotocol.h"

namespace tests {

class RealTimeClockMessageTest : public QObject
{
    Q_OBJECT

private slots:
    void testCreateRequest();
};

void RealTimeClockMessageTest::testCreateRequest()
{
    qmwp::RealTimeClockMessage message;
    message.setDate(QDate(2013, 12, 27));
    message.setTime(QTime(23,56));
    qmwp::core::Protocol protocol = message.createProtocol();
    QCOMPARE(protocol.type(), static_cast<quint8>(0x26));
    QByteArray payload = protocol.payload();
    QCOMPARE(payload.at(0), static_cast<char>(0x07));
    QCOMPARE(payload.at(1), static_cast<char>(0xdd));
    QCOMPARE(payload.at(2), static_cast<char>(0x0c));
    QCOMPARE(payload.at(3), static_cast<char>(0x1b));
    QCOMPARE(payload.at(4), static_cast<char>(0x05));
    QCOMPARE(payload.at(5), static_cast<char>(0x17));
    QCOMPARE(payload.at(6), static_cast<char>(0x38));
    QCOMPARE(payload.at(7), static_cast<char>(0x00));
}

}

QTEST_MAIN(tests::RealTimeClockMessageTest)
#include "moc_realtimeclockmessagetest.cpp"
