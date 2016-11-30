cmake_minimum_required(VERSION 3.6)
project(ninjatool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Qt5Widgets)
set(CMAKE_AUTOMOC TRUE)
find_package(RapidJSON REQUIRED)

set(SOURCES main.cpp mainwindow.cpp mainwindow.h objecttype.cpp objecttype.h objecttypescene.cpp objecttypescene.h documentwidget.h ninjatoolsettingswidget.cpp ninjatoolsettingswidget.h settingsmanager.cpp settingsmanager.h settingsconstants.cpp settingsconstants.h)
set(RESOURCES Icons/document-new.svg Icons/document-open.svg Icons/document-properties.svg Icons/preferences-system.svg)

add_executable(ninjatool ${SOURCES} ${RESOURCES})

if (APPLE)
    SET_TARGET_PROPERTIES(ninjatool PROPERTIES MACOSX_BUNDLE TRUE)
    SET_TARGET_PROPERTIES(ninjatool PROPERTIES RESOURCE TRUE)
    set_source_files_properties(${RESOURCES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
else()
    add_custom_command(TARGET ninjatool POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Icons ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Icons COMMENT "Copying Action Icons")
endif()

target_link_libraries(ninjatool ninjacore Qt5::Widgets)
include_directories(../ninjacore ${RapidJSON_INCLUDE_DIRS})
