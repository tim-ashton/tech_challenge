#include "FlightInfoOne.h"

namespace tech_challenge {

FlightInfoOne::FlightInfoOne()
{}

FlightInfoOne::~FlightInfoOne()
{}

bool FlightInfoOne::canHandleMessage(const std::string &message) const
{
    return m_parser.canHandleMessage(message);
}
    
bool FlightInfoOne::messageToData(const std::string &message)
{
    return m_parser.messageToT(message, m_data);
}

std::string FlightInfoOne::dbInsertQuery()
{
    int calculatedValue = m_data.x_data * m_data.y_data;
    return "INSERT INTO F1 VALUES ("+std::to_string(calculatedValue)+")";
}

FlightInfoOneData FlightInfoOne::data()
{
    return m_data;
}

}