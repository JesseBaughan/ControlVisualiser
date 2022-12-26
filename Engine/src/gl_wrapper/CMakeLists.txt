# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.10)

# Project name
project(gl_wrapper)

set(GL3W_DIR ${CMAKE_SOURCE_DIR}/libs/gl3w)
set(LIBS_DIR ${CMAKE_SOURCE_DIR}/libs)

set(GL_SOURCES 
    index_buffer.cpp 
    vertex_buffer.cpp
    vertex_array.cpp
    shader.cpp
    renderer.cpp
)

add_library(gl_wrapper ${GL_SOURCES})

target_include_directories(gl_wrapper PUBLIC ${GL3W_DIR})
target_include_directories(gl_wrapper PUBLIC ${LIBS_DIR})