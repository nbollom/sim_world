cmake_minimum_required(VERSION 3.15)
project(simworld)

set(CMAKE_CXX_STANDARD 20)

find_package(SQLite3)

add_library(simworld SHARED simworld.cpp simworld.h components.h material.cpp material.h database.cpp database.h query.cpp query.h)
include_directories(${SQLite3_INCLUDE_DIR})
target_link_libraries(simworld ${SQLite3_LIBRARY})