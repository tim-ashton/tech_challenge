#include "FlightInfoTwo_test.h"

namespace tech_challenge {
namespace test{

TEST_P(FlightInfoTwo_test, ParamTestCorrectFormedJson) {

    FlightInfoTwoTestData testData = GetParam();

    FlightInfoTwo infoTwo;

    bool canHandle = infoTwo.canHandleMessage(testData.m_jsonStrParam);
    EXPECT_EQ(testData.m_expectedCanHanleResult, canHandle);

    // Can't do the rest of the test if unable to handle this msg.
    if(!canHandle)
        return;

    infoTwo.messageToData(testData.m_jsonStrParam);

    EXPECT_STREQ(testData.m_expectedResultData.str_data.c_str(), infoTwo.data().str_data.c_str());
    EXPECT_EQ(testData.m_expectedResultData.expected_str_length, infoTwo.data().expected_str_length);
    EXPECT_STREQ(testData.m_expectedResultDbQuery.c_str(), infoTwo.dbInsertQuery().c_str());
}

}}