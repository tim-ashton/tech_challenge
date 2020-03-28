#include "MessageReceiver.h"
#include "Utils.h"


namespace tech_challenge {

const int MessageReceiver::CHECKSUM_BYTE_POSITION = 0;
const int MessageReceiver::CHECKSUM_LEN_BYTES = 8;

const int MessageReceiver::SEQUENCE_NUM_BYTE_POSITION = 8;
const int MessageReceiver::SEQUENCE_NUM_LEN_BYTES = 4;

const int MessageReceiver::DATA_PAYLOAD_BYTE_POSITION = 12;

MessageReceiver::MessageReceiver()
    : m_currentSequenceNumber(0)
{}
    
MessageReceiver::~MessageReceiver()
{}

void MessageReceiver::setJsonPayloadReadyCallback(
    std::function<void(std::string&&)> function)
{
    m_jsonPayloadReadyFunc = function;
}

void MessageReceiver::handleUdpData(std::string &&data)
{
    std::string checksumBytes = data.substr(CHECKSUM_BYTE_POSITION, CHECKSUM_LEN_BYTES);
    std::string sequenceNumberBytes = data.substr(SEQUENCE_NUM_BYTE_POSITION, SEQUENCE_NUM_LEN_BYTES);
    std::string dataPayload = data.substr(DATA_PAYLOAD_BYTE_POSITION, std::string::npos);

    uint64_t checksum = *(reinterpret_cast<uint64_t*>(checksumBytes.data()));
    uint32_t sequenceNumber = *(reinterpret_cast<uint32_t*>(sequenceNumberBytes.data()));

    // drop message if incorrect checksum
    if(checksum != calculateChecksum(dataPayload))
        return;

    // Check the sequence number.
    // if we are ahead. just keep the latest.
    // if we recieve apacket from the past drop it. with the exception of wrapping.
    if(!isAfterCurrentSequenceNum(sequenceNumber))
        return;
    
    m_currentSequenceNumber = sequenceNumber;

    if(m_jsonPayloadReadyFunc)
        m_jsonPayloadReadyFunc(std::move(dataPayload));
}

bool MessageReceiver::isAfterCurrentSequenceNum(uint32_t number)
{
    if(m_currentSequenceNumber < number && (number - m_currentSequenceNumber) < 0x80000000)
        return true;

    if(m_currentSequenceNumber > number && (m_currentSequenceNumber - number) > 0x80000000)
        return true;

    return false;
    // // allow any number to start.
    // if(number > m_currentSequenceNumber && m_currentSequenceNumber == 0)
    //     return true;

    // const uint16_t max  = 0xFFFF;

    // uint16_t first = (m_currentSequenceNumber - number) % max;
    // uint16_t second = (number - m_currentSequenceNumber) % max;
    // if(first > second)
    //     return true;
    
    // return false;
}

}