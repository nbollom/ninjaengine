cmake_minimum_required(VERSION 3.6)
project(ninjatool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Qt5Widgets)
set(CMAKE_AUTOMOC TRUE)

add_executable(ninjatool main.cpp mainwindow.cpp mainwindow.h objecttype.cpp objecttype.h objecttypescene.cpp objecttypescene.h)
target_link_libraries(ninjatool ninjacore Qt5::Widgets)
include_directories(../ninjacore)
