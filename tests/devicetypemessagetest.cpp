
#include <QtTest/QtTest>

#include <QByteArray>

#include "testconfig.h"

#include "devicetypemessage.h"
#include "core/metawatchprotocol.h"

namespace tests {

class DeviceTypeMessageTest : public QObject
{
    Q_OBJECT

private slots:
    void testCreateRequest();
    void testCreateResponse();
};

void DeviceTypeMessageTest::testCreateRequest()
{
    qmwp::DeviceTypeMessage message;
    qmwp::core::Protocol protocol = message.createProtocol();
    QCOMPARE(protocol.type(), static_cast<quint8>(0x01));
    QCOMPARE(protocol.option(), static_cast<quint8>(0x00));
    QCOMPARE(protocol.payload().size(), 0);
}

void DeviceTypeMessageTest::testCreateResponse()
{
    qmwp::DeviceTypeMessage message;

    qmwp::core::Protocol protocol;
    //protocol.setOption(0x05);
    QByteArray payload;
    payload[0] = 0x05;
    protocol.setPayload(payload);

    message.handle(protocol);

    QCOMPARE(message.responseType(), 0x02);
    QVERIFY(message.deviceType() == qmwp::DeviceTypeMessage::Type::DIGITAL_WATCH_GEN2);
}

}

QTEST_MAIN(tests::DeviceTypeMessageTest)
#include "moc_devicetypemessagetest.cpp"

