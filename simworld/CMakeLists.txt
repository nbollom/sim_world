cmake_minimum_required(VERSION 3.15)
project(simworld)

set(CMAKE_CXX_STANDARD 20)

find_package (SQLite3)

add_library(simworld SHARED simworld.cpp simworld.h components.h material.cpp material.h)
include_directories(${SQLITE3_INCLUDE_DIRS})
target_link_libraries (simworld ${SQLITE3_LIBRARIES})