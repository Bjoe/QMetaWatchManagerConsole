#ifndef QMWP_CORE_METAWATCHPROTOCOL_H
#define QMWP_CORE_METAWATCHPROTOCOL_H

#include <memory>

#include <QString>
#include <QByteArray>

namespace qmwp {
namespace core {

class Protocol
{
public:
    Protocol();
    ~Protocol();

    Protocol(const Protocol& copy);
    Protocol& operator=(const Protocol& other);

    bool isValid() const;
    QString lastError() const;

    quint8 type() const;
    void setType(quint8 type);

    quint8 option() const;
    void setOption(quint8 option);

    QByteArray payload() const;
    void setPayload(const QByteArray& payload);

    QByteArray createMessage() const;
    static Protocol createProtocol(const QByteArray &message);

private:
    class Private;
    std::unique_ptr<Private> m_priv;
};

} // namespace core
} // namespace qmwp

#endif // QMWP_CORE_METAWATCHPROTOCOL_H
