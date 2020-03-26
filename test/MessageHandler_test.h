#pragma once
#include "gtest/gtest.h"

#include "MessageHandler.h"

namespace tech_challenge {
namespace test{

/*
Test setup for the MessageHandler class

Notes:

No need to test each database query is correctly generated as this is
independently tested for each FlightInfo (handler) class.
*/

class MessageHandler_test : public ::testing::Test {

public:
    MessageHandler_test(){}
    ~MessageHandler_test(){}
};

struct HandlerCallbackTestData
{
    std::string testMessage;
    int expectedCallbackFiredCount;
};

class MessageHandlerCallsBack : public MessageHandler_test,
                public testing::WithParamInterface<HandlerCallbackTestData> {

public:
    int callbackReceivedCount;

    MessageHandlerCallsBack()
        : callbackReceivedCount(0)
    {}

    ~MessageHandlerCallsBack(){}
  
    void onDbQueryRecieved(std::string &&str)
    {
        ++callbackReceivedCount;
    }
};

INSTANTIATE_TEST_SUITE_P(callBackFiredCorrectly,
                         MessageHandlerCallsBack, 
                         testing::Values(
    // failure cases
    HandlerCallbackTestData{R"({"x":15,"y":99})", 0},
    HandlerCallbackTestData{R"(bad_string)", 0},

    // The FlightInfo classes have been independently tested.
    // These tests really just check that they are plugged in
    // and that we are ready to receive messages of that kind

    // first handler 
    HandlerCallbackTestData{R"({"x_data":15,"y_data":99})", 1}



    // Add tests for more handlers here
));


}}