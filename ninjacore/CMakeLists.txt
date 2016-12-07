cmake_minimum_required(VERSION 3.6)
project(ninjacore)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SDL2_BUILDING_LIBRARY ON)
find_package(SDL2 REQUIRED image ttf mixer)
find_package(RapidJSON REQUIRED)

add_subdirectory(anax)

add_library(ninjacore SHARED ninjacore.h resource_manager.cpp resource_manager.h image.cpp image.h window_manager.cpp window_manager.h window.cpp window.h types.h SDL2/sdl2_window.cpp SDL2/sdl2_window.h)
target_link_libraries(ninjacore PRIVATE ${SDL2_LIBRARIES} anax)
include_directories(${SDL2_INCLUDE_DIR} ${RapidJSON_INCLUDE_DIRS} anax)
