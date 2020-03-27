#pragma once
#include "gtest/gtest.h"

#include "FlightInfoTwo.h"

#include "ParserJsonConverters.h"

namespace tech_challenge {
namespace test{

struct FlightInfoTwoTestData
{
    std::string m_jsonStrParam;

    FlightInfoTwoData m_expectedResultData;
    std::string m_expectedResultDbQuery;
    bool m_expectedCanHanleResult;
};

class FlightInfoTwo_test : public testing::TestWithParam<FlightInfoTwoTestData>
{
public:
    FlightInfoTwo_test(){}
    ~FlightInfoTwo_test(){}
};

INSTANTIATE_TEST_SUITE_P(ParamTestCorrectFormedJson, 
                         FlightInfoTwo_test,
                         testing::Values(
    // Can handle
    FlightInfoTwoTestData{R"({"str_data":"12345","expected_str_length":5})", FlightInfoTwoData{"12345", 5}, "INSERT INTO F2 VALUES true", true},
    FlightInfoTwoTestData{R"({"str_data":"1","expected_str_length":2})", FlightInfoTwoData{"1", 2}, "INSERT INTO F2 VALUES false", true},
    FlightInfoTwoTestData{R"({"str_data":"123","expected_str_length":3})", FlightInfoTwoData{"123", 3}, "INSERT INTO F2 VALUES true", true},

    // Rejects incompatable json string another handler handles this
    FlightInfoTwoTestData{R"({"x_data":100,"y_data":99})", FlightInfoTwoData{"", 0}, "", false}
));

}}