cmake_minimum_required(VERSION 3.6)
project(testing)

set(CMAKE_CXX_STANDARD 11)

include_directories(${INCLUDES} inc)

set(SOURCE_FILES main.cpp)
add_executable(testing ${SOURCE_FILES})