cmake_minimum_required(VERSION 3.6)
project(ninjaengine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(ninjaengine main.cpp)
target_link_libraries(ninjaengine ninjacore)