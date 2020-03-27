#include "MessageHandler.h"

namespace tech_challenge {


const int MessageHandler::MAX_QUEUED_MESSAGES = 1000;
const int MessageHandler::Q_RCV_TIMEOUT_MS = 50;

MessageHandler::MessageHandler()
    : m_terminate(false)
{
    initParserModules();
}

MessageHandler::~MessageHandler()
{
    stop();
}

// Could be done outside the class to decouple the modules from this handler
void MessageHandler::initParserModules()
{
    m_parserModules.emplace_back(std::make_unique<FlightInfoOne>());
    m_parserModules.emplace_back(std::make_unique<FlightInfoTwo>());

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
                    for(auto &module : m_parserModules)
                    {
                        if(module->canHandleMessage(message))
                        {
                            // This handler can deal with the message
                            // so go ahead and fire the callback
                            module->messageToData(message);
                            if(m_dataBaseQueryReady)
                                m_dataBaseQueryReady(module->dbInsertQuery());
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

    if(m_handlerThread)
    {
        if(m_handlerThread->joinable())
            m_handlerThread->join();

        m_handlerThread.reset();
    }

    // Allow restarts.
    m_terminate = false;
}

}