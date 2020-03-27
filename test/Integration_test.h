#pragma once
#include "gtest/gtest.h"

#include "MessageHandler.h"
#include "MockConnectionHandler.h"
#include "MockDbManager.h"

/*
By mocking up the databas and connection handlers we can now
do some integration testing to check
that all the modules work together as expected.

Here we can dummy up how the whole system should fit together.
*/

namespace tech_challenge {
namespace test{


class Integration_test : public ::testing::Test
{
public:

    static const int MAX_DB_QUERY_RECEIVE_WAIT_TIME_MS;

    std::unique_ptr<MessageHandler> m_messageHandler;
    std::unique_ptr<MockConnectionHandler> m_connectionHandler;
    std::unique_ptr<MockDbManager> m_dbManager;

    Integration_test(){}
    ~Integration_test(){}

    void initialize();
};

}}