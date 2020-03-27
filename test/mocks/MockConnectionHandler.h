#pragma once
#include "BaseConnectionHandler.h"

namespace tech_challenge {
namespace test {

class MockConnectionHandler : BaseConnectionHandler
{
public:

    MockConnectionHandler(
        std::unique_ptr<MessageReceiver> messageReceiver,
        std::string groupAddress,
        uint16_t portNumber);
        
    ~MockConnectionHandler();

    void recieveDummyUdpPayload(std::string &&payload);

};

}}