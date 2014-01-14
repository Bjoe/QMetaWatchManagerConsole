#include "metawatchmessage.h"

namespace qmwp {
namespace core {

Message::~Message()
{

}

core::Protocol Message::createProtocol() const
{
    core::Protocol protocol;
    m_requestHandler(protocol);
    return protocol;
}

int Message::responseType() const
{
    return m_responseType;
}

void Message::handle(Protocol &protocol)
{
    m_responseHandler(protocol);
}

Message::Message(std::function<void (Protocol &)> request,
                 std::function<void (Protocol &)> response,
                 int responseType)
    : m_requestHandler(request),
      m_responseHandler(response),
      m_responseType(responseType)
{

}

} // namespace core
} // namespace qmwp
