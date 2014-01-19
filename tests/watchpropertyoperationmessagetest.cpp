
#include <QtTest/QtTest>

#include "testconfig.h"

#include "watchpropertyoperationmessage.h"
#include "core/metawatchprotocol.h"

namespace tests {

class WatchPropertOperationMessageTest : public QObject
{
    Q_OBJECT

private slots:
    void testCreateRequest();
    void testResponse();
};

void WatchPropertOperationMessageTest::testCreateRequest()
{
    qmwp::WatchPropertyOperationMessage message;
    message.setClockFormatChecked(true);
    message.setDateFormatChecked(true);

    qmwp::core::Protocol protocol = message.createProtocol();

    QCOMPARE(protocol.type(), static_cast<quint8>(0x30));
    QCOMPARE(protocol.option(), static_cast<quint8>(0x03));
}

void WatchPropertOperationMessageTest::testResponse()
{
    qmwp::core::Protocol protocol;
    protocol.setOption(0x83);

    qmwp::WatchPropertyOperationMessage message;
    message.handle(protocol);

    QCOMPARE(message.responseType(), 0x31);
    QVERIFY(message.clockFormatChecked());
    QVERIFY(message.clockFormat() == qmwp::WatchPropertyOperationMessage::ClockFormat::H24);
    QVERIFY(message.dateFormatChecked());
    QVERIFY(message.dateFormat() == qmwp::WatchPropertyOperationMessage::DateFormat::DDMM);
    QVERIFY(message.autoBacklightChecked() == false);
    QVERIFY(message.autoBacklight() == qmwp::WatchPropertyOperationMessage::Backlight::DISABLE);
}

}

QTEST_MAIN(tests::WatchPropertOperationMessageTest)
#include "moc_watchpropertyoperationmessagetest.cpp"

