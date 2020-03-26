#pragma once

#include <string>
#include <functional>
#include <vector>
#include <memory>

#include "ThreadSafeQueue.h"
#include "FlightInfoOne.h"
#include "FlightInfoTwo.h"

namespace tech_challenge {

class MessageHandler
{
    std::function<void(std::string&&)> m_dataBaseQueryReady;
    std::vector<std::unique_ptr<BaseFlightInfo>> m_flightInfoHandlers;
    std::unique_ptr<std::thread> m_handlerThread;
    ThreadSafeQueue<std::string> m_queue;
    bool m_terminate;

public:

    static const int MAX_QUEUED_MESSAGES;
    static const int Q_RCV_TIMEOUT_MS;

    MessageHandler(const MessageHandler&) = delete;
    MessageHandler& operator=(const MessageHandler&) = delete;

    MessageHandler();
    ~MessageHandler();

    void setDbQueryReadyCallback(std::function<void(std::string&&)> function);

    /*
    Queues any incoming messages for processing.
    */
    void onMessageRecieved(std::string &&message);

    /*
    Start the handler thread for dealing with queued messages
    Note: only allows starting thread once.
    This maybe could return an enum or at least a bool to indicate what happed when called if required.
    */
    void start();

    /*
    Stop the running thread.
    */
    void stop();

private:
    /*
    Initialize a list of potential handlers for incoming
    Messages.
    */
    void initFlightInfoHandlerList();
};


}
    
