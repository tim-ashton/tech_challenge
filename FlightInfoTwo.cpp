#include "FlightInfoTwo.h"

namespace tech_challenge {

FlightInfoTwo::FlightInfoTwo()
{}

FlightInfoTwo::~FlightInfoTwo()
{}

bool FlightInfoTwo::canHandleMessage(const std::string &message) const
{
    return m_parser.canHandleMessage(message);
}

bool FlightInfoTwo::messageToData(const std::string &message)
{
    return m_parser.messageToT(message, m_data);
}

std::string FlightInfoTwo::dbInsertQuery()
{
    return "todo";
}

FlightInfoTwoData FlightInfoTwo::data()
{
    return m_data;
}

}