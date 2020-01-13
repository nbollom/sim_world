cmake_minimum_required(VERSION 3.15)
project(sim)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(sim main.cpp)
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/third_party/imgui ${CMAKE_SOURCE_DIR}/third_party/gl3w/include ${OPENGL_INCLUDE_DIR})
target_link_libraries(sim simworld glfw ${OPENGL_gl_LIBRARY} imgui)