#include "FlightInfoOne_test.h"

namespace tech_challenge {
namespace test{

TEST_P(FlightInfoOne_test, ParamTestCorrectFormedJson) {

    TestData testData = GetParam();

    FlightInfoOne infoOne;

    EXPECT_TRUE(infoOne.canHandleMessage(testData.m_jsonStrParam));

    infoOne.messageToData(testData.m_jsonStrParam);

    EXPECT_EQ(testData.m_expectedResultData.x_data, infoOne.data().x_data);
    EXPECT_EQ(testData.m_expectedResultData.y_data, infoOne.data().y_data);
    EXPECT_STREQ(testData.m_expectedResultDbQuery.c_str(), infoOne.dbInsertQuery().c_str());

}

}}