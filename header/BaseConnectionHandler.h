#pragma once

#include "MessageReceiver.h"

#include <memory>
#include <string>

namespace tech_challenge {

/*
Provides a base class for a connection handler.
This allows us to mock up some end to end unit tests.
*/
class BaseConnectionHandler
{
protected:
    std::unique_ptr<MessageReceiver> m_messageReciever;
    const std::string m_groupAddress;
    const uint16_t m_port;
public:

    BaseConnectionHandler(
        std::unique_ptr<MessageReceiver> messageReceiver,
        std::string groupAddress,
        uint16_t portNumber);
        
    virtual ~BaseConnectionHandler();
};

}

