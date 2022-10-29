# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.10)

# Project name
project(ControlVisualiser)

# Use c++11
set(CMAKE_CXX_STANDARD 11)


set(IMGUI_DIR libs/imgui)
set(GL3W_DIR libs/gl3w)
set(GL_DIR src/gl_wrapper)
set(LIBS_DIR libs)

set(SOURCES 
    src/main.cpp
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    #${GL3W_DIR}/GL/gl3w.c
)

# Setup output directories.
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Add in the openGL wrapper library
add_subdirectory(${GL_DIR})

# Add all the source files needed to build the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Make sure we get all compiler output
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

#target_link_libraries(${PROJECT_NAME} ${GL_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC ${GL3W_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${IMGUI_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${IMGUI_DIR}/backends)
target_include_directories(${PROJECT_NAME} PUBLIC ${GL_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBS_DIR})

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS ">>> Linux")

    find_package(glfw3 REQUIRED)
    target_link_libraries(${PROJECT_NAME} glfw)
endif()