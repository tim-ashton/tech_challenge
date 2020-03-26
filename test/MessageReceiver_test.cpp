#include "MessageReceiver_test.h"
#include "Utils.h"

namespace tech_challenge {
namespace test {




TEST_F(MessageReceiver_test, goodDataCallsBack) 
{

    int callbackFiredCount = 0;

    std::string sequenceNum = serializeUint16t(1);
    std::string checksum = serializeUint64t(calculateChecksum(R"({"x_data":15,"y_data":99})"));

    MessageReceiver receiver;
    receiver.setJsonPayloadReadyCallback([&](std::string &&)->void
        {
            ++callbackFiredCount;
        });

    receiver.handleUdpData(checksum + sequenceNum + R"({"x_data":15,"y_data":99})");

    EXPECT_EQ(callbackFiredCount, 1);
}

TEST_F(MessageReceiver_test, badChecksumNoCallback) 
{

    int callbackFiredCount = 0;

    std::string sequenceNum = serializeUint16t(1);
    std::string checksum = serializeUint64t(0xFFFF);

    MessageReceiver receiver;
    receiver.setJsonPayloadReadyCallback([&](std::string &&)->void
        {
            ++callbackFiredCount;
        });

    receiver.handleUdpData(checksum + sequenceNum + R"({"x_data":15,"y_data":99})");

    EXPECT_EQ(callbackFiredCount, 0);
}

TEST_F(MessageReceiver_test, incorrectSequenceNoCallback) 
{

    int callbackFiredCount = 0;

    
    std::string checksum = serializeUint64t(calculateChecksum(R"({"x_data":15,"y_data":99})"));

    MessageReceiver receiver;
    receiver.setJsonPayloadReadyCallback([&](std::string &&)->void
        {
            ++callbackFiredCount;
        });

    std::string sequenceNum = serializeUint16t(1);
    receiver.handleUdpData(checksum + sequenceNum + R"({"x_data":15,"y_data":99})");

    sequenceNum = serializeUint16t(0);
    receiver.handleUdpData(checksum + sequenceNum + R"({"x_data":15,"y_data":99})");

    EXPECT_EQ(callbackFiredCount, 1);
}

TEST_F(MessageReceiver_test, sequenceSkipsButCallsback) 
{

    int callbackFiredCount = 0;

    
    std::string checksum = serializeUint64t(calculateChecksum(R"({"x_data":15,"y_data":99})"));

    MessageReceiver receiver;
    receiver.setJsonPayloadReadyCallback([&](std::string &&)->void
        {
            ++callbackFiredCount;
        });

    std::string sequenceNum = serializeUint16t(1);
    receiver.handleUdpData(checksum + sequenceNum + R"({"x_data":15,"y_data":99})");

    // This time we the sequence has skipped ahead
    sequenceNum = serializeUint16t(55);
    receiver.handleUdpData(checksum + sequenceNum + R"({"x_data":15,"y_data":99})");

    EXPECT_EQ(callbackFiredCount, 2);
}

TEST_F(MessageReceiver_test, sequenceHandlesWrapping) 
{

    int callbackFiredCount = 0;

    
    std::string checksum = serializeUint64t(calculateChecksum(R"({"x_data":15,"y_data":99})"));

    MessageReceiver receiver;
    receiver.setJsonPayloadReadyCallback([&](std::string &&)->void
        {
            ++callbackFiredCount;
        });

    std::string sequenceNum = serializeUint16t(6);
    receiver.handleUdpData(checksum + sequenceNum + R"({"x_data":15,"y_data":99})");

    // This is an earlier sequence number and should be dropped.
    sequenceNum = serializeUint16t(65535);
    receiver.handleUdpData(checksum + sequenceNum + R"({"x_data":15,"y_data":99})");

    EXPECT_EQ(callbackFiredCount, 1);
}

}}