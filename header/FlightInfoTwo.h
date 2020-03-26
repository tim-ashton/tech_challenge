#pragma once

#include "BaseFlightInfo.h"
#include "Parser.h"
#include "FlightInfoTwoData.h"

namespace tech_challenge {

/*
A concrete implementation of a BaseFlightInfo.

Uses a templated parser to extract data into the data container.
*/
class FlightInfoTwo : public BaseFlightInfo
{
    Parser<FlightInfoTwoData> m_parser;
    FlightInfoTwoData m_data;

public:
    FlightInfoTwo();
    ~FlightInfoTwo();

    bool canHandleMessage(const std::string &message) const override;
    
    bool messageToData(const std::string &message) override;

    std::string dbInsertQuery() override;

    FlightInfoTwoData data();
};

}