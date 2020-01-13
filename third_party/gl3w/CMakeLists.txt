cmake_minimum_required(VERSION 3.1.3 FATAL_ERROR)

project(gl3w)

set(CMAKE_POSITION_INDEPENDENT_CODE ON) # -fPIC

set(SOURCE_DIR src)
set(HEADER_DIR include)

set(HEADER_FILES
	"${HEADER_DIR}/GL/gl3w.h"
	"${HEADER_DIR}/GL/glcorearb.h"
	"${HEADER_DIR}/KHR/khrplatform.h"
)

set(SOURCE_FILES
	"${SOURCE_DIR}/gl3w.c"
)

# add and depend on OpenGL
find_package(OpenGL REQUIRED)

# create gl3w target
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
include_directories(${HEADER_DIR})
if(DEFINED EXTERNAL_INCLUDE_DIRS)
	target_include_directories(${PROJECT_NAME} INTERFACE ${EXTERNAL_INCLUDE_DIRS})
endif()
# let remote project know which libraries need to be linked
target_link_libraries(${PROJECT_NAME} INTERFACE ${EXTERNAL_LIBRARIES} ${CMAKE_DL_LIBS})
