cmake_minimum_required(VERSION 3.15)
project(simulator)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(OpenGL_GL_PREFERENCE GLVND)

add_subdirectory(third_party)
add_subdirectory(simworld)
add_subdirectory(sim)
