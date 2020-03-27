#pragma once

#include "ParserJsonConverters.h"

#include <string>
#include <nlohmann/json.hpp>

namespace tech_challenge {
    

/*
This class handles some parsing for JSON to data structures.
If the data in recieved messages required a different format
in the future then this could be replaced/updated to handle 
the new format

Note: 
T must be copy constructable.

Requires implementaion of from_json as per nlohmann/json library requirements,
see ParserJsonConverters
*/
template<class T>
class Parser
{
protected:

public:

    Parser(){};
    virtual ~Parser(){};

    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;
    
    /*
    True if the message in the string can be converted to T
    */
    bool canHandleMessage(const std::string &message) const
    {
        try
        {
            auto json = nlohmann::json::parse(message);
            auto j = json.get<T>();
        }
        catch(const std::exception& e)
        {
            return false;
        }
        return true;
    }
    
    /*
    Converts the out param to type T from the message.
    returns true if successful or false if failed.
    T must by copy constructable.
    */
    bool messageToT(const std::string &message, T &out) const
    {
        if(!canHandleMessage(message))
            return false;
        
        out = nlohmann::json::parse(message).get<T>();
        return true;
    }
};


} // end namespace