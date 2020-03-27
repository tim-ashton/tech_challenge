#include "MockDbManager.h"

namespace tech_challenge {
namespace test {

void MockDbManager::onQueryReady(std::string &&preparedQuery)
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_recievedQueries.emplace_back(std::move(preparedQuery));
    }
    m_condition.notify_one();
}

}}