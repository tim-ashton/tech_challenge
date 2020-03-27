
cmake_minimum_required (VERSION 3.0.2)
project (${CMAKE_PROJECT_NAME}_test)

add_subdirectory(googletest)

set(SOURCES
    main.cpp
    ThreadSafeQueue_test.cpp
    Parser_test.cpp
    FlightInfoOne_test.cpp
    FlightInfoTwo_test.cpp
    MessageHandler_test.cpp
    MessageReceiver_test.cpp
    Integration_test.cpp

    #mocks
    mocks/MockConnectionHandler.cpp
    mocks/MockDbManager.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    .
    ../
    ../header
    mocks
)

target_link_libraries(${PROJECT_NAME} lib${CMAKE_PROJECT_NAME} gtest gtest_main)



