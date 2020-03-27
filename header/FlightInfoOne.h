#pragma once

#include "BaseParserModule.h"
#include "Parser.h"
#include "FlightInfoOneData.h"

namespace tech_challenge {

/*
An implementation of a BaseParserModule.

Uses a templated parser to extract data into the data container.
*/

class FlightInfoOne : public BaseParserModule
{
    Parser<FlightInfoOneData> m_parser;
    FlightInfoOneData m_data;

public:
    FlightInfoOne();
    ~FlightInfoOne();

    bool canHandleMessage(const std::string &message) const override;
    
    bool messageToData(const std::string &message) override;

    std::string dbInsertQuery() override;

    FlightInfoOneData data();
};

}