cmake_minimum_required(VERSION 3.6)
project(testing)

set(CMAKE_CXX_STANDARD 11)

include_directories(${INCLUDES} inc)

set(SOURCE_FILES main.cpp inc/Console_ASCII.h src/Console_ASCII.cpp inc/MVC/Controller.h inc/MVC/Model.h
        inc/MVC/Observer.h inc/MVC/View.h src/MVC/Controller.cpp src/MVC/Model.cpp src/MVC/View.cpp)
add_executable(testing ${SOURCE_FILES})