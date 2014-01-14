#ifndef QMWP_CORE_METAWATCHMESSAGE_H
#define QMWP_CORE_METAWATCHMESSAGE_H

#include <functional>

#include "core/metawatchprotocol.h"

namespace qmwp {
namespace core {

class Message
{
public:
    Message() =default;
    virtual ~Message();

    Protocol createProtocol() const;
    int responseType() const;
    void handle(Protocol& protocol);

protected:
    Message(std::function<void (Protocol&)> request,
            std::function<void (Protocol&)> response,
            int responseType);

private:
    std::function<void (Protocol&)> m_requestHandler = {};
    std::function<void (Protocol&)> m_responseHandler = {};
    int m_responseType = 0;
};

} // namespace core
} // namespace qmwp

#endif // QMWP_CORE_METAWATCHMESSAGE_H
