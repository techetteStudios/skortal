cmake_minimum_required(VERSION 3.6)
project(skortal)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp BluefruitConfig.h)
add_executable(skortal ${SOURCE_FILES})