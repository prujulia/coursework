cmake_minimum_required(VERSION 3.6)
project(UserInterface)

SET("OpenCV_DIR" "C:/opencv/build/x64/vc14/lib")

find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Test.cpp 
    Source.cpp 
    Header.h)

add_executable(UserInterface ${SOURCE_FILES})
target_link_libraries( UserInterface ${OpenCV_LIBS} )