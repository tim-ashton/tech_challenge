#pragma once
#include "gtest/gtest.h"

#include "Parser.h"

namespace tech_challenge {
namespace test{

struct TestFlightInfo
{
    std::string str_data;
    int int_data;
    double double_data;
};

void from_json(const nlohmann::json& j, TestFlightInfo& f) 
{
    f.str_data = j.at("str_data").get<std::string>();
    f.int_data = j.at("int_data").get<int>();
    f.double_data = j.at("double_data").get<double>();
}

class Parser_test : public ::testing::Test {

public:
    Parser_test(){}
    ~Parser_test(){}
};

}}