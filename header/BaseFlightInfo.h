#pragma once

// #include "Parser.h"

#include <string>

namespace tech_challenge {

class BaseFlightInfo {

public:
    BaseFlightInfo(){};
    virtual ~BaseFlightInfo(){};

    /*
    True if the message can be handled by this flight info
    */
    virtual bool canHandleMessage(const std::string &message) const = 0;

    /*
    Converts a message into whatever the derived classes data object is
    */
    virtual bool messageToData(const std::string &message) = 0;

    /*
    return a prepared db insert query from parsed message data.
    */
    virtual std::string dbInsertQuery() = 0;
};



} // end namespace