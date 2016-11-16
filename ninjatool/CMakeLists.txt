cmake_minimum_required(VERSION 3.6)
project(ninjatool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Qt5Widgets)
set(CMAKE_AUTOMOC TRUE)
find_package(RapidJSON REQUIRED)

add_executable(ninjatool main.cpp mainwindow.cpp mainwindow.h objecttype.cpp objecttype.h objecttypescene.cpp objecttypescene.h documentwidget.h ninjatoolsettingswidget.cpp ninjatoolsettingswidget.h settingsmanager.cpp settingsmanager.h)
add_custom_command(TARGET ninjatool POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Icons 
${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Icons COMMENT "Copying Action Icons")
target_link_libraries(ninjatool ninjacore Qt5::Widgets)
include_directories(../ninjacore ${RapidJSON_INCLUDE_DIRS})
