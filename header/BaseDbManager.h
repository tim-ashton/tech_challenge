#pragma once

#include <string>

namespace tech_challenge {

/*
Provides an interface of a database manager allowing
us to mock up some end to end unit tests.
*/
class BaseDbManager
{
public:

    BaseDbManager(){};
    virtual ~BaseDbManager(){}

    virtual void onQueryReady(std::string &&preparedQuery) = 0;
};

}