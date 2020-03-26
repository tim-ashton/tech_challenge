#include "ThreadSafeQueue_test.h"
#include <random>

namespace tech_challenge {
namespace test{

/*
Basic check that contents can be queued.
*/
TEST_F(ThreadSafeQueue_test, pushAddsCorrectNumberOfItems) 
{
    ThreadSafeQueue<int> queue;

    for(int i = 0; i < 10; i++)
        queue.push(std::move(i));

    for(int i = 0; i < 10; i++){
        int result;
        queue.try_pop(result, std::chrono::milliseconds(0));
        EXPECT_EQ(i, result);
    }
}

/*
Test that the queue contents are correct and that try_pop can 
fail if there is no data within the timeout period.
*/
TEST_F(ThreadSafeQueue_test, try_popTimesOutOccasionallyAllItemsStillRecieved) 
{
    ThreadSafeQueue<int> queue;

    const int numbItems = 250;

    std::thread producer([&queue]()->void 
    {
        std::mt19937_64 eng{std::random_device{}()};
        std::uniform_int_distribution<> dist {1, 15};

        for(int i = 0; i < numbItems; i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds{dist(eng)});
            queue.push(std::move(i));
        }
    });

    std::thread consumer([&queue]()->void 
    {
        int expectedVal = 0;
        bool alwaysSucceededPop = true;

        while(expectedVal < numbItems)
        {
            int result;
            if(queue.try_pop(result, std::chrono::milliseconds(2)))
            {
                EXPECT_EQ(expectedVal, result);
                ++expectedVal;
            }
            else
            {
                alwaysSucceededPop = false;
            }
        }
        EXPECT_FALSE(alwaysSucceededPop);
    });

    producer.join();
    consumer.join();

}


}}