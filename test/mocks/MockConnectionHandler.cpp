#include "MockConnectionHandler.h"

namespace tech_challenge {
namespace test {

MockConnectionHandler::MockConnectionHandler(
    std::unique_ptr<MessageReceiver> messageReceiver,
    std::string groupAddress,
    uint16_t portNumber)
    : BaseConnectionHandler(std::move(messageReceiver), groupAddress, portNumber)
{}
    
MockConnectionHandler::~MockConnectionHandler()
{}

void MockConnectionHandler::recieveDummyUdpPayload(std::string &&payload)
{
    m_messageReciever->handleUdpData(std::move(payload));
}

}}