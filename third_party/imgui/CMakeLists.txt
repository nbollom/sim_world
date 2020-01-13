cmake_minimum_required(VERSION 3.15)
project(imgui)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(
        imgui SHARED
        imconfig.h
        imgui.h
        imgui.cpp
        imgui_draw.cpp
        imgui_internal.h
        imgui_impl_glfw.h
        imgui_impl_glfw.cpp
        imgui_impl_opengl3.h
        imgui_impl_opengl3.cpp
        imgui_widgets.cpp
        imstb_rectpack.h
        imstb_textedit.h
        imstb_truetype.h
    )

include_directories(${CMAKE_SOURCE_DIR}/third_party/gl3w/include ${OPENGL_INCLUDE_DIR})
target_link_libraries(imgui glfw ${OPENGL_gl_LIBRARY} gl3w)
