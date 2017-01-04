cmake_minimum_required(VERSION 3.6)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

add_subdirectory(ninjaengine)
add_subdirectory(ninjacore)
add_subdirectory(ninjatool)

if(APPLE)
    set(BUILD_SHARED_LIBS NO) #fix SQLiteCpp linking on osx
endif(APPLE)

option(SQLITECPP_RUN_CPPCHECK "Run cppcheck C++ static analysis tool." OFF)
option(SQLITECPP_RUN_CPPLINT "Run cpplint.py tool for Google C++ StyleGuide." OFF)

add_subdirectory(SQLiteCpp)

