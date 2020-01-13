cmake_minimum_required(VERSION 3.15)
project(simworld)

set(CMAKE_CXX_STANDARD 20)

add_library(simworld SHARED simworld.cpp simworld.h components.h)
