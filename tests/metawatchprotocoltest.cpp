
#include <QtTest/QtTest>

#include "testconfig.h"

#include <QString>
#include <QByteArray>

#include "core/metawatchprotocol.h"

namespace tests {
class MetaWatchProtocolTest : public QObject
{
    Q_OBJECT

private slots:
    void testWithouthPayload();
    void testWithPayload();
};

void MetaWatchProtocolTest::testWithouthPayload()
{
    qmwp::core::Protocol protocol;
    QByteArray message = protocol.createMessage();
    QCOMPARE(message.at(0), static_cast<char>(0x01));
    QCOMPARE(message.at(1), static_cast<char>(0x06));
    QCOMPARE(message.at(2), static_cast<char>(0x00));
    QCOMPARE(message.at(3), static_cast<char>(0x00));
    QCOMPARE(message.at(4), static_cast<char>(0x93));
    QCOMPARE(message.at(5), static_cast<char>(0xc2));
}

void MetaWatchProtocolTest::testWithPayload()
{
    QByteArray bytes;
    bytes.append(0x23);
    bytes.append(0x42);
    bytes.append(0x65);

    qmwp::core::Protocol protocol;

    protocol.setType(0x20);
    protocol.setOption(0x30);
    protocol.setPayload(bytes);

    QByteArray message = protocol.createMessage();
    QCOMPARE(message.at(0), static_cast<char>(0x01));
    QCOMPARE(message.at(1), static_cast<char>(0x09));
    QCOMPARE(message.at(2), static_cast<char>(0x20));
    QCOMPARE(message.at(3), static_cast<char>(0x30));
    QCOMPARE(message.at(4), static_cast<char>(0x23));
    QCOMPARE(message.at(5), static_cast<char>(0x42));
    QCOMPARE(message.at(6), static_cast<char>(0x65));
    QCOMPARE(message.at(7), static_cast<char>(0x12));
    QCOMPARE(message.at(8), static_cast<char>(0x16));
}

}

QTEST_MAIN(tests::MetaWatchProtocolTest)
#include "moc_metawatchprotocoltest.cpp"
