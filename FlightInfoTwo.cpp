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
    std::string queryP1 = "INSERT INTO F2 VALUES ";
    std::string queryP2  = (m_data.expected_str_length == m_data.str_data.size()) ? "true" : "false";
    std::string query = queryP1 + queryP2;
    return query;
}

FlightInfoTwoData FlightInfoTwo::data()
{
    return m_data;
}

}