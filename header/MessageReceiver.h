#pragma once

#include <string>
#include <stdint.h>
#include <memory>
#include <functional>

namespace tech_challenge {

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
    bool isAfterCurrentSequenceNum(uint16_t number);
   
};

}