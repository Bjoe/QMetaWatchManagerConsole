#ifndef QMWP_CORE_PROTOCOLDISPATCHER_H
#define QMWP_CORE_PROTOCOLDISPATCHER_H

#include <memory>
#include <QObject>
#include <QIODevice>

#include "core/metawatchprotocol.h"
#include "core/metawatchmessage.h"

namespace qmwp {
namespace core {

class ProtocolDispatcher
{
public:
    ProtocolDispatcher();
    ~ProtocolDispatcher();

    void initializeDevice(QIODevice *device);
    qint64 send(const Message *message);

    void addHandler(Message *handler);

    void dispatch(Protocol protocol);

private:
    class Private;
    std::unique_ptr<Private> m_priv;
};

} // namespace core
} // namespace qmwp

#endif // QMWP_CORE_PROTOCOLDISPATCHER_H
