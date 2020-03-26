#include "Parser_test.h"

namespace tech_challenge {
namespace test{


TEST_F(Parser_test, canHandleMessageRejectsMalformedString) 
{
    Parser<TestFlightInfo> parser;
    EXPECT_FALSE(parser.canHandleMessage("Bad JSON"));
    EXPECT_FALSE(parser.canHandleMessage(""));
    EXPECT_FALSE(parser.canHandleMessage("{\"incorrect\" : \"fields\"}"));
}

TEST_F(Parser_test, canHandleMessageRejectsWhenWrongType) 
{
    Parser<int> parser;
    std::string testStr = R"({"str_data":"a string","int_data":99,"double_data":10.5})";
    EXPECT_FALSE(parser.canHandleMessage(testStr));
}

TEST_F(Parser_test, canHandleMessageAcceptsCorrectlyFormedString) 
{
    Parser<TestFlightInfo> parser;
    std::string testStr = R"({"str_data":"a string","int_data":99,"double_data":10.5})";
    EXPECT_TRUE(parser.canHandleMessage(testStr));
}

TEST_F(Parser_test, messageToTReturnsStructureWhenGivenCorrectJsonString) 
{
    std::string testStr = R"({"str_data":"a string","int_data":99,"double_data":10.5})";

    Parser<TestFlightInfo> parser;
    TestFlightInfo result;
    EXPECT_TRUE(parser.messageToT(testStr, result));

    EXPECT_STREQ(result.str_data.c_str(), "a string");
    EXPECT_DOUBLE_EQ(result.double_data, 10.5);
    EXPECT_EQ(result.int_data, 99);

}


}} // end namespace