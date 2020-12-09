cmake_minimum_required(VERSION 3.15)
project(sim)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

set(SIM_FILES
        editor_menu.cpp
        editor_menu.h
        main.cpp
        main_menu.cpp
        main_menu.h
        menu.h
        menu.cpp
        menu_stack.cpp
        menu_stack.h
        state.h
        settings_menu.cpp
        settings_menu.h
        settings.cpp
        settings.h
)

if (DEBUG)
    add_definitions(-DDEBUG=1)
endif (DEBUG)


add_executable(sim ${SIM_FILES})
include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/third_party/imgui
        ${CMAKE_SOURCE_DIR}/third_party/gl3w/include
        ${CMAKE_SOURCE_DIR}/third_party/json/include
        ${OPENGL_INCLUDE_DIR}
)
target_link_libraries(sim simworld glfw ${OPENGL_gl_LIBRARY} imgui nlohmann_json::nlohmann_json)
