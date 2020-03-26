
cmake_minimum_required (VERSION 3.8.0)
project (tech_challenge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(test)

add_executable (${CMAKE_PROJECT_NAME} 
    main.cpp
    FlightInfoOne.cpp
    FlightInfoTwo.cpp
    MessageHandler.cpp
    MessageReceiver.cpp
    Utils.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE 
    header
)

target_link_libraries(${CMAKE_PROJECT_NAME} -lpthread)

# set(HEADER_FILES 
#     ThreadSafeQueue.h
# )

# add_library(lib${CMAKE_PROJECT_NAME} 
#     ${HEADER_FILES}

# )