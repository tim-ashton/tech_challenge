
#pragma once

#include <string>
#include <stdint.h>

namespace tech_challenge {

/*
Generates a basic checksum on a std::string
param check: the string to generate a checksum for
*/
uint64_t calculateChecksum (std::string check);

/*
Convert a uint64_t to a hex string representation

eg fffffffffffffe0c
*/
std::string toHexString(uint64_t value);

std::string serializeUint64t(uint64_t value);
std::string serializeUint32t(uint32_t value);


std::string prepareUdpPayload(
    uint32_t sequnceNum, 
    const std::string &jsonData, bool makeBadChecksum = false);

}