# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.10)

# Project name
project(ControlVisualiser)

# Use c++14
set(CMAKE_CXX_STANDARD 14)

# Set paths 
set(IMGUI_DIR libs/imgui)
set(GL3W_DIR libs/gl3w)
set(ENGINE_DIR Engine)
set(LIBS_DIR libs/)
set(PLATFORM_DIR Platform)

find_package(glfw3 CONFIG REQUIRED)

# OpenGL
# target OpenGL::GL since https://cmake.org/cmake/help/v3.8/module/FindOpenGL.html
set(OpenGL_GL_PREFERENCE "GLVND")
include(FindOpenGL)
if(NOT OPENGL_FOUND)
  message(FATAL_ERROR "OpenGL library was not found)")
endif()

set(SOURCES 
    ${ENGINE_DIR}/src/Application.cpp
    ${ENGINE_DIR}/src/Window.cpp
    ${ENGINE_DIR}/src/Renderer/Renderer.cpp
    ${ENGINE_DIR}/src/Renderer/Buffer.cpp
    ${ENGINE_DIR}/src/Renderer/Shader.cpp
    ${ENGINE_DIR}/src/Renderer/VertexArray.cpp
    ${ENGINE_DIR}/src/Renderer/RenderCommand.cpp
    ${ENGINE_DIR}/src/Renderer/RendererAPI.cpp
    ${ENGINE_DIR}/src/Renderer/Renderer.cpp
    ${ENGINE_DIR}/src/ImGui/ImGuiRenderer.cpp
    ${ENGINE_DIR}/src/OrthographicCamera.cpp
    ${ENGINE_DIR}/src/Layer.cpp
    ${ENGINE_DIR}/src/LayerStack.cpp
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    ${PLATFORM_DIR}/Linux/LinuxWindow.cpp
    ${PLATFORM_DIR}/OpenGL/OpenGLContext.cpp
    ${PLATFORM_DIR}/OpenGL/OpenGLBuffer.cpp
    ${PLATFORM_DIR}/OpenGL/OpenGLVertexArray.cpp
    ${PLATFORM_DIR}/OpenGL/OpenGLRenderer.cpp
    ${PLATFORM_DIR}/OpenGL/OpenGLRendererAPI.cpp
    ./SandBox/SandboxApp.cpp
)

# Add our unit tests
add_subdirectory(test)

# Add GTest
add_subdirectory(${LIBS_DIR}/googletest)

# Add all the source files needed to build the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Make sure we get all compiler output
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra)

target_include_directories(${PROJECT_NAME} PUBLIC ${GL3W_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${IMGUI_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBS_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC build/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${PLATFORM_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ./)
target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC SandBox)
target_include_directories(${PROJECT_NAME} PUBLIC SandBox/assets)

target_link_libraries(${PROJECT_NAME} PRIVATE
  glfw
  OpenGL::GL)

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

# select an OpenGL loader with choices GL3W, GLEW or GLAD
set(OPENGL_LOADER "GL3W" CACHE STRING
  "Dear ImGui OpenGL loader (GL3W, GLEW, GLAD or custom header)")
set_property(CACHE OPENGL_LOADER PROPERTY STRINGS "GL3W;GLEW;GLAD")

if(OPENGL_LOADER STREQUAL "GL3W")
  message(STATUS "Using OpenGL loader gl3w")
  target_compile_definitions(${PROJECT_NAME} PRIVATE
    IMGUI_IMPL_OPENGL_LOADER_GL3W)
  target_sources(${PROJECT_NAME} PRIVATE
    ${GL3W_DIR}/GL/gl3w.c
    ${GL3W_DIR}/GL/gl3w.h)
  target_include_directories(${PROJECT_NAME} PRIVATE
    ${GL3W_DIR})
  target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CMAKE_DL_LIBS}) # -ldl, see https://cmake.org/cmake/help/v3.0/variable/CMAKE_DL_LIBS.html
elseif(OPENGL_LOADER STREQUAL "GLEW")
  message(STATUS "Using OpenGL loader glew")
  include(FindGLEW)
  if(NOT GLEW_FOUND)
    message(FATAL_ERROR "GLEW library was not found)")
  endif()
  target_compile_definitions(${PROJECT_NAME} PRIVATE
    IMGUI_IMPL_OPENGL_LOADER_GLEW)
  target_include_directories(${PROJECT_NAME} PRIVATE
    ${GLEW_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} PRIVATE
    ${GLEW_LIBRARIES})
elseif(OPENGL_LOADER STREQUAL "GLAD")
  message(STATUS "Using OpenGL loader glad")
  target_compile_definitions(${PROJECT_NAME} PRIVATE
    IMGUI_IMPL_OPENGL_LOADER_GLAD)
  target_sources(${PROJECT_NAME} PRIVATE
    ../libs/glad/src/glad.c
    ../libs/glad/include/glad/glad.h
    ../libs/glad/include/KHR/khrplatform.h)
  target_include_directories(${PROJECT_NAME} PRIVATE
    ../libs/glad/include)
  target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CMAKE_DL_LIBS}) # -ldl, see https://cmake.org/cmake/help/v3.0/variable/CMAKE_DL_LIBS.html
else()
  message(FATAL_ERROR "Unhandled OpenGL loader '${OPENGL_LOADER}'")
endif()