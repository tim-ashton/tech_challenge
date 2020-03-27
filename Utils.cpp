#include "Utils.h"

#include <sstream>
#include <iomanip>

namespace tech_challenge {

uint64_t calculateChecksum (std::string check) 
{
    uint64_t result = 0;
    for(auto & c : check)
        result -= c;
    return result;
}

std::string toHexString(uint64_t value)
{
    std::stringstream s;
    s << std::hex << std::setfill('0') << std::setw(16) << value;
    return s.str();
}

std::string serializeUint64t(uint64_t value)
{
    std::string bytes;
    for(int i = 0; i < sizeof(uint64_t); i++)
    {
        bytes += (value >> (i*8));
    }
    return bytes;
}

std::string serializeUint16t(uint16_t value)
{
    std::string bytes;
    for(int i = 0; i < sizeof(uint16_t); i++)
    {
        bytes += (value >> (i*8));
    }
    return bytes;
}
    
std::string prepareUdpPayload(
    uint16_t sequnceNum, 
    const std::string &jsonData, bool makeBadChecksum)
{
    std::string sequenceNum = serializeUint16t(sequnceNum);
    std::string checksum;

    if(makeBadChecksum)
        checksum = serializeUint64t(calculateChecksum(""));
    else
        checksum = serializeUint64t(calculateChecksum(jsonData));

    return checksum + sequenceNum + jsonData;
}

}