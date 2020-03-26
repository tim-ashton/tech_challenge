#include "MessageHandler.h"

namespace tech_challenge {


const int MessageHandler::MAX_QUEUED_MESSAGES = 1000;
const int MessageHandler::Q_RCV_TIMEOUT_MS = 50;

MessageHandler::MessageHandler()
    : m_terminate(false)
{
    initFlightInfoHandlerList();
}

MessageHandler::~MessageHandler()
{
    stop();
}

void MessageHandler::initFlightInfoHandlerList()
{
    m_flightInfoHandlers.emplace_back(std::make_unique<FlightInfoOne>());
    m_flightInfoHandlers.emplace_back(std::make_unique<FlightInfoTwo>());

    // Add new FlightInfo objects for new message types
}

void MessageHandler::setDbQueryReadyCallback(std::function<void(std::string&&)> function)
{
    m_dataBaseQueryReady = function;
}

void MessageHandler::onMessageRecieved(std::string &&message)
{
    if(m_queue.size() < MAX_QUEUED_MESSAGES)
        m_queue.push(std::move(message));
}

void MessageHandler::start()
{
    if(!m_handlerThread)
    {
        m_handlerThread = std::make_unique<std::thread>([this]()->void
        {
            std::string message;
            while(!m_terminate)
            {
                // give 100ms before timing out.
                if(m_queue.try_pop(message, std::chrono::milliseconds(Q_RCV_TIMEOUT_MS)))
                {
                    for(auto &f : m_flightInfoHandlers)
                    {
                        if(f->canHandleMessage(message))
                        {
                            // This handler can deal with the message
                            // so go ahead and fire the callback
                            f->messageToData(message);
                            if(m_dataBaseQueryReady)
                                m_dataBaseQueryReady(f->dbInsertQuery());
                        }
                    }
                }
                // no message received. Don't do anything.
            }
        });
    }
}

void MessageHandler::stop()
{
    m_terminate = true;
    if(m_handlerThread->joinable())
        m_handlerThread->join();

    m_handlerThread.reset();
    m_terminate = false;
}

}