
cmake_minimum_required (VERSION 3.0.2)
project (${CMAKE_PROJECT_NAME}_test)

add_subdirectory(googletest)

set(SOURCES
    ThreadSafeQueue_test.cpp
    Parser_test.cpp
    FlightInfoOne_test.cpp
    MessageHandler_test.cpp
    MessageReceiver_test.cpp

    ../FlightInfoOne.cpp
    ../FlightInfoTwo.cpp
    ../MessageHandler.cpp
    ../MessageReceiver.cpp
    ../Utils.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    .
    ../
    ../header
)

target_link_libraries(${PROJECT_NAME} gtest gtest_main)



