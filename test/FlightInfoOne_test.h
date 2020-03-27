#pragma once
#include "gtest/gtest.h"

#include "FlightInfoOne.h"

#include "ParserJsonConverters.h"

namespace tech_challenge {
namespace test{

struct TestData
{
    std::string m_jsonStrParam;

    FlightInfoOneData m_expectedResultData;
    std::string m_expectedResultDbQuery;
    bool m_expectedCanHanleResult;
};

class FlightInfoOne_test : public testing::TestWithParam<TestData>
{
public:
    FlightInfoOne_test(){}
    ~FlightInfoOne_test(){}
};

INSTANTIATE_TEST_SUITE_P(ParamTestCorrectFormedJson, 
                         FlightInfoOne_test,
                         testing::Values(
    TestData{R"({"x_data":15,"y_data":99})", FlightInfoOneData{15, 99}, "INSERT INTO F1 VALUES (1485)", true},
    TestData{R"({"x_data":1,"y_data":438})", FlightInfoOneData{1, 438}, "INSERT INTO F1 VALUES (438)", true},
    TestData{R"({"x_data":100,"y_data":99})", FlightInfoOneData{100, 99}, "INSERT INTO F1 VALUES (9900)", true},

    // Rejects incompatable json string another handler handles this
    TestData{R"({"str_data":"123","expected_str_length":3})", FlightInfoOneData{0, 0}, "", false}
));

}}