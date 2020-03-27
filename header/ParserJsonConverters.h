#pragma once

#include <nlohmann/json.hpp>

#include "FlightInfoOneData.h"
#include "FlightInfoTwoData.h"

namespace tech_challenge {

inline void from_json(const nlohmann::json& j, FlightInfoOneData& f)
{
    f.x_data = j.at("x_data").get<int>();
    f.y_data = j.at("y_data").get<int>();
}

inline void from_json(const nlohmann::json& j, FlightInfoTwoData& f)
{
    f.str_data = j.at("str_data").get<std::string>();
    f.expected_str_length = j.at("expected_str_length").get<int>();
}

}