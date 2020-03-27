#include "Integration_test.h"

#include "Utils.h"
#include "MessageReceiver.h"

using namespace std::placeholders;

namespace tech_challenge {
namespace test{

const int Integration_test::MAX_DB_QUERY_RECEIVE_WAIT_TIME_MS = 200;

void Integration_test::initialize()
{
    m_messageHandler = std::make_unique<MessageHandler>();

    auto messageReceiver = std::make_unique<MessageReceiver>();

    // The reciever calls the handlers onMessageRecieved function
    // when it has recieved udp payload and validated message structure
    // The message handler takes the json string.
    messageReceiver->setJsonPayloadReadyCallback(
        std::bind(&MessageHandler::onMessageRecieved, m_messageHandler.get(), _1));

    // connection owns the receiver.
    m_connectionHandler = std::make_unique<MockConnectionHandler>(std::move(messageReceiver), "unused_addr", 0);

    m_dbManager = std::make_unique<MockDbManager>();

    // connect the db manager callback
    m_messageHandler->setDbQueryReadyCallback(
        std::bind(&MockDbManager::onQueryReady, m_dbManager.get(), _1));

    // Fire it up.
    m_messageHandler->start();
}

/*

Note:

Each component of the system has already been tested so we know that everything
is working along each step of the journey of a message throught the system.

As such we will keep integration testing to a minimum and simply veryfy that integration
is OK.
*/

// Do a simple test for a success case to realize setup of the system.
TEST_F(Integration_test, integrationOk)
{
    initialize();

    // dummy up receiving data from the socket
    m_connectionHandler->recieveDummyUdpPayload(prepareUdpPayload(1, R"({"x_data":15,"y_data":99})"));


    // Use a condition here instead of a sleep
    std::unique_lock<std::mutex> lock(m_dbManager->m_mutex);
    if(!m_dbManager->m_condition.wait_for(
        lock, 
        std::chrono::milliseconds(MAX_DB_QUERY_RECEIVE_WAIT_TIME_MS), 
        [this] { return !m_dbManager->m_recievedQueries.empty(); }))
    {
        FAIL(); // didn't receive the message.
    }

    EXPECT_EQ(1, m_dbManager->m_recievedQueries.size());
    EXPECT_STREQ("INSERT INTO F1 VALUES (1485)", m_dbManager->m_recievedQueries.front().c_str());

}

}}