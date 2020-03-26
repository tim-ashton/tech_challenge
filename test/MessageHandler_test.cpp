#include "MessageHandler_test.h"

namespace tech_challenge {
namespace test{

using namespace std::placeholders;

TEST_F(MessageHandler_test, maxMessagesQueuedIfNotStarted)
{
    int callbackFiredCount = 0;

    MessageHandler handler;
    handler.setDbQueryReadyCallback([&](std::string &&)->void
        {
            ++callbackFiredCount;
        });

    for(int i = 0; i < MessageHandler::MAX_QUEUED_MESSAGES * 2; i++)
    {
        handler.onMessageRecieved(R"({"x_data":15,"y_data":99})");
    }

    // Start processing after pushing messages
    handler.start();

    // I really dislike the idea of using a sleep in a unit test as they are indeterminate
    // but this gives a simple test for this demonstation and this isdefinitely enough time.
    std::this_thread::sleep_for(
        std::chrono::milliseconds(MessageHandler::Q_RCV_TIMEOUT_MS * 2));

    EXPECT_EQ(MessageHandler::MAX_QUEUED_MESSAGES, callbackFiredCount);
}

TEST_F(MessageHandler_test, messagesDroppedWhenCallbackNotSet)
{
    int callbackFiredCount = 0;

    MessageHandler handler;
    
    for(int i = 0; i < MessageHandler::MAX_QUEUED_MESSAGES * 2; i++)
    {
        handler.onMessageRecieved(R"({"x_data":15,"y_data":99})");
    }

    // Start processing after pushing messages
    handler.start();

    // I really dislike the idea of using a sleep in a unit test as they are indeterminate
    // but this gives a simple test for this demonstation and this is
    // definitely enough time.
    std::this_thread::sleep_for(
        std::chrono::milliseconds(MessageHandler::Q_RCV_TIMEOUT_MS * 2));


    // Now we finally set the callback. but it is too late. the messages 
    // have been discarded
        handler.setDbQueryReadyCallback([&](std::string &&)->void
        {
            ++callbackFiredCount;
        });


    EXPECT_EQ(0, callbackFiredCount);
}

TEST_F(MessageHandler_test, startingStopping)
{
    int callbackFiredCount = 0;

    MessageHandler handler;
    handler.setDbQueryReadyCallback([&](std::string &&)->void
        {
            ++callbackFiredCount;
        });

    // Start processing
    handler.start();
    handler.stop();
    
    for(int i = 0; i < MessageHandler::MAX_QUEUED_MESSAGES * 2; i++)
    {
        handler.onMessageRecieved(R"({"x_data":15,"y_data":99})");
    }

    // I really dislike the idea of using a sleep in a unit test as they are indeterminate
    // but this gives a simple test for this demonstation and this is
    // definitely enough time.
    std::this_thread::sleep_for(
        std::chrono::milliseconds(MessageHandler::Q_RCV_TIMEOUT_MS * 2));

    // No callbacks fired. Thread is stopped.
    EXPECT_EQ(0, callbackFiredCount);

    // Startup again. now the messages will be processed
    handler.start();
    
    std::this_thread::sleep_for(
        std::chrono::milliseconds(MessageHandler::Q_RCV_TIMEOUT_MS * 2));

    EXPECT_EQ(MessageHandler::MAX_QUEUED_MESSAGES, callbackFiredCount);   
}

TEST_P(MessageHandlerCallsBack, callBackFiredCorrectly) 
{

    auto testData = GetParam();

    MessageHandler handler;
    handler.start(); // need a running thread to process msgs

    handler.setDbQueryReadyCallback(
        std::bind(&MessageHandlerCallsBack::onDbQueryRecieved, this, _1));

    handler.onMessageRecieved(std::move(testData.testMessage));

    // I really dislike the idea of using a sleep in a unit test as they are indeterminate
    // but this gives a simple test for this demonstation and this is
    // definitely enough time.
    std::this_thread::sleep_for(
        std::chrono::milliseconds(MessageHandler::Q_RCV_TIMEOUT_MS * 2));

    EXPECT_EQ(testData.expectedCallbackFiredCount, callbackReceivedCount);
}


}}