#include "MessageReceiver_test.h"
#include "Utils.h"

namespace tech_challenge {
namespace test {




TEST_F(MessageReceiver_test, goodDataCallsBack) 
{

    int callbackFiredCount = 0;

    MessageReceiver receiver;
    receiver.setJsonPayloadReadyCallback([&](std::string &&)->void
        {
            ++callbackFiredCount;
        });

    receiver.handleUdpData(prepareUdpPayload(1, R"({"x_data":15,"y_data":99})"));

    EXPECT_EQ(callbackFiredCount, 1);
}

TEST_F(MessageReceiver_test, badChecksumNoCallback) 
{

    int callbackFiredCount = 0;

    std::string sequenceNum = serializeUint32t(1);
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

    receiver.handleUdpData(prepareUdpPayload(1, R"({"x_data":15,"y_data":99})"));

    // This is an earlier message so should be rejected.
    receiver.handleUdpData(prepareUdpPayload(0, R"({"x_data":15,"y_data":99})"));

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

    receiver.handleUdpData(prepareUdpPayload(1, R"({"x_data":15,"y_data":99})"));

    // This time we the sequence has skipped ahead, we should accept this later packet
    receiver.handleUdpData(prepareUdpPayload(55, R"({"x_data":15,"y_data":99})"));

    EXPECT_EQ(callbackFiredCount, 2);
}

TEST_F(MessageReceiver_test, sequenceHandlesWrapping) 
{
    int callbackFiredCount = 0;

    MessageReceiver receiver;
    receiver.setJsonPayloadReadyCallback([&](std::string &&)->void
        {
            ++callbackFiredCount;
        });

    receiver.handleUdpData(prepareUdpPayload(6, R"({"x_data":15,"y_data":99})"));

    // This is an earlier sequence number and should be dropped.
    receiver.handleUdpData(prepareUdpPayload(0xFFFFFFFF - 10, R"({"x_data":15,"y_data":99})"));

    EXPECT_EQ(callbackFiredCount, 1);
}

}}