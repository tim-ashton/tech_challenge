#include "FlightInfoOne_test.h"

namespace tech_challenge {
namespace test{

TEST_P(FlightInfoOne_test, ParamTestCorrectFormedJson) {

    TestData testData = GetParam();

    FlightInfoOne infoOne;

    bool canHandle = infoOne.canHandleMessage(testData.m_jsonStrParam);
    EXPECT_EQ(testData.m_expectedCanHanleResult, canHandle);

    // Can't do the rest of the test if unable to handle this msg.
    if(!canHandle)
        return;

    infoOne.messageToData(testData.m_jsonStrParam);

    EXPECT_EQ(testData.m_expectedResultData.x_data, infoOne.data().x_data);
    EXPECT_EQ(testData.m_expectedResultData.y_data, infoOne.data().y_data);
    EXPECT_STREQ(testData.m_expectedResultDbQuery.c_str(), infoOne.dbInsertQuery().c_str());

}

}}