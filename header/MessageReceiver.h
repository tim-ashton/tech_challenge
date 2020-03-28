#pragma once

#include <string>
#include <stdint.h>
#include <memory>
#include <functional>

namespace tech_challenge {

/*
The MessageReceiver handles a UDP packet from the connection.

It validates the message, strips out the json part and passes
it to the registered callback.

This could live in the Message Handler but it would be easier to extend
later, for example to handle multiple json payloads in one udp packet.

Assumptions:
Only a single message is sent in a UDP packet.

*/

class MessageReceiver
{
    std::function<void(std::string&&)> m_jsonPayloadReadyFunc;
    uint16_t m_currentSequenceNumber;

public:

    static const int CHECKSUM_BYTE_POSITION;
    static const int CHECKSUM_LEN_BYTES;

    static const int SEQUENCE_NUM_BYTE_POSITION;
    static const int SEQUENCE_NUM_LEN_BYTES;
    
    static const int DATA_PAYLOAD_BYTE_POSITION;

    static const uint16_t SEQUENCE_LIMIT_BOUND;

    MessageReceiver(const MessageReceiver&) = delete;
    MessageReceiver& operator=(const MessageReceiver&) = delete;

    MessageReceiver();
    ~MessageReceiver();

    void setJsonPayloadReadyCallback(std::function<void(std::string&&)> function);

    void handleUdpData(std::string &&data);

private:
    bool isAfterCurrentSequenceNum(uint32_t number);
   
};

}