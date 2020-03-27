#include "BaseConnectionHandler.h"

namespace tech_challenge {

BaseConnectionHandler::BaseConnectionHandler(
    std::unique_ptr<MessageReceiver> messageReceiver,
    std::string groupAddress,
    uint16_t portNumber)
    : m_messageReciever(std::move(messageReceiver))
    , m_groupAddress(groupAddress)
    , m_port(portNumber)
{}
    
BaseConnectionHandler::~BaseConnectionHandler()
{}

}