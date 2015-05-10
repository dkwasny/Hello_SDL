cmake_minimum_required(VERSION 2.8)

set(CMAKE_PREFIX_PATH .)
ENABLE_LANGUAGE(C)
ENABLE_LANGUAGE(CXX)

project(Hello_SDL CXX)

add_executable(hello_world src/hello_world.cpp src/point.h)
find_package(OpenGL REQUIRED)
find_library(sdl_lib SDL2)
target_link_libraries(hello_world ${sdl_lib} ${OPENGL_LIBRARIES})

if(MSVC)
	find_library(sdl_main_lib SDL2main)
	target_link_libraries(hello_world ${sdl_main_lib})
endif()

include_directories(include ${OPENGL_INCLUDE_DIRS})
