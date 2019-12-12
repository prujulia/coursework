cmake_minimum_required(VERSION 3.6)

project(UserInterface)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(SOURCE_FILES Test.cpp Source.cpp Header.h)
add_executable(arrstack ${SOURCE_FILES})