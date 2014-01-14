
#include <QtTest/QtTest>

#include "testconfig.h"

#include "core/metawatchprotocol.h"
#include "core/metawatchmessage.h"
#include "devicetypemessage.h"

#include "core/protocoldispatcher.h"

namespace tests {

class ProtocolDispatcherTest : public QObject
{
    Q_OBJECT

private slots:
    void testExample();
};

void ProtocolDispatcherTest::testExample()
{
    qmwp::core::ProtocolDispatcher dispatcher;

    qmwp::DeviceTypeMessage message;

    dispatcher.addHandler(&message);

    qmwp::core::Protocol protocol;
    protocol.setType(0x02);
    protocol.setOption(0x05);

    dispatcher.dispatch(protocol);

    QVERIFY(message.deviceType() == qmwp::DeviceTypeMessage::Type::DIGITAL_WATCH_GEN2);
}

}

QTEST_MAIN(tests::ProtocolDispatcherTest)
#include "moc_protocoldispatchertest.cpp"
