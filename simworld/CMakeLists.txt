cmake_minimum_required(VERSION 3.15)
project(simworld)

set(CMAKE_CXX_STANDARD 20)

find_package(SQLite3 REQUIRED)
find_package(Lua REQUIRED)

set(SIMWORLD_FILES
        components.h
        database.cpp
        database.h
        material.cpp
        material.h
        query.cpp
        query.h
        simworld.cpp
        simworld.h
        world.cpp
        world.h
        world_type.cpp
        world_type.h
        lua_engine.cpp
        lua_engine.h)

add_library(simworld SHARED ${SIMWORLD_FILES})
include_directories(${SQLite3_INCLUDE_DIR} ${LUA_INCLUDE_DIR})
target_link_libraries(simworld ${SQLite3_LIBRARY} ${LUA_LIBRARY} ${LUA_MATH_LIBRARY})
