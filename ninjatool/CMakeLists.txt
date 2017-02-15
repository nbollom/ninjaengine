cmake_minimum_required(VERSION 3.6)
project(ninjatool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Qt5Widgets)
set(CMAKE_AUTOMOC TRUE)
find_package(RapidJSON REQUIRED)

set(SOURCES main.cpp mainwindow.cpp mainwindow.h settingsmanager.cpp settingsmanager.h settingsconstants.cpp settingsconstants.h carousel.h carousel.cpp projectmanager.cpp projectmanager.h)
set(ICONS Icons/document-new.svg Icons/document-open.svg Icons/document-properties.svg Icons/preferences-system.svg)
if(APPLE)
    set(APP_ICON Icons/icon.icns)
endif(APPLE)
set(EDITORS editors/documentwidget.h editors/settingswidget.cpp editors/settingswidget.h editors/newproject.cpp editors/newproject.h editors/newwidget.h editors/newwidget.cpp)

add_executable(ninjatool ${SOURCES} ${EDITORS} ${ICONS} ${APP_ICON})

if (APPLE)
    SET_TARGET_PROPERTIES(ninjatool PROPERTIES MACOSX_BUNDLE TRUE)
    SET_TARGET_PROPERTIES(ninjatool PROPERTIES RESOURCE TRUE)
    set(MACOSX_BUNDLE_ICON_FILE icon)
    set_source_files_properties(${ICONS} ${APP_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
else(APPLE)
    add_custom_command(TARGET ninjatool POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Icons ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Icons COMMENT "Copying Action Icons")
endif(APPLE)

target_link_libraries(ninjatool ninjacore Qt5::Widgets sqlite3)
include_directories(../ninjacore ${RapidJSON_INCLUDE_DIRS})
