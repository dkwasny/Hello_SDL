cmake_minimum_required(VERSION 3.0)
set(CMAKE_PREFIX_PATH .)
project(Hello_SDL CXX)

add_executable(hello_world src/hello_world.cpp src/point.h)

find_package(OpenGL REQUIRED)

find_library(sdl_lib SDL2)
find_library(sdl_main_lib SDL2main)
target_link_libraries(hello_world ${sdl_lib} ${sdl_main_lib} ${OPENGL_LIBRARIES})

include_directories(include ${OPENGL_INCLUDE_DIRS})