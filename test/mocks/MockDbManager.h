#pragma once

#include "BaseDbManager.h"

#include <vector>
#include <mutex>
#include <condition_variable>

namespace tech_challenge {
namespace test {

/*
Provides an interface of a database manager allowing
us to mock up some end to end unit tests.
*/
class MockDbManager : BaseDbManager
{
public:

    std::vector<std::string> m_recievedQueries;
    mutable std::mutex m_mutex;
    std::condition_variable m_condition;

    MockDbManager(){};
    ~MockDbManager(){};

    void onQueryReady(std::string &&preparedQuery) override;
};

}}