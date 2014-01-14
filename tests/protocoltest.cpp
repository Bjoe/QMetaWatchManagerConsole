
#include <QtTest/QtTest>

#include <QByteArray>
#include <QString>

#include <boost/crc.hpp>
#include <boost/cstdint.hpp>

#include "testconfig.h"

#include "core/metawatchprotocol.h"

namespace tests {

class ProtocolTest : public QObject
{
    Q_OBJECT

private slots:
    void testCreateProtocol();
};

void ProtocolTest::testCreateProtocol()
{
    QByteArray bytes;
    bytes[0] = 0x01;
    bytes[1] = 0x07;
    bytes[2] = 0x31;
    bytes[3] = 0xff;
    bytes[4] = 0x23;

    boost::crc_basic<16>  crc_ccitt( 0x1021, 0xFFFF, 0, true, false );
    crc_ccitt.process_bytes( bytes.constData(), 5 );
    quint16 crc = crc_ccitt.checksum();

    bytes.append(crc % 256);
    bytes.append(crc / 256);

    qmwp::core::Protocol protocol = qmwp::core::Protocol::createProtocol(bytes);
    QCOMPARE(protocol.lastError(), QString(""));
    QVERIFY(protocol.isValid());
    QCOMPARE(protocol.type(), static_cast<quint8>(0x31));
    QCOMPARE(protocol.option(), static_cast<quint8>(0xff));
    QCOMPARE(protocol.payload().size(), 1);
}

}

QTEST_MAIN(tests::ProtocolTest)
#include "moc_protocoltest.cpp"

