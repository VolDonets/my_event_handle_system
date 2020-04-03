cmake_minimum_required(VERSION 3.13)
project(observer_test)

set(CMAKE_CXX_STANDARD 20)

add_executable(observer_test main.cpp
        my_events/event_handler.h)