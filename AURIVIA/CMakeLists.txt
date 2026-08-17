cmake_minimum_required(VERSION 3.16)
project(AURIVIA VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project structure
set(ENGINE_DIR ${CMAKE_SOURCE_DIR}/engine)
set(EDITOR_DIR ${CMAKE_SOURCE_DIR}/editor)
set(BINDINGS_DIR ${CMAKE_SOURCE_DIR}/bindings)
set(SAMPLES_DIR ${CMAKE_SOURCE_DIR}/samples)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Include directories
include_directories(
    ${ENGINE_DIR}/core/include
    ${ENGINE_DIR}/renderer/include
    ${ENGINE_DIR}/physics/include
    ${ENGINE_DIR}/audio/include
    ${ENGINE_DIR}/input/include
    ${ENGINE_DIR}/scripting/include
)

# Core engine sources
set(ENGINE_SOURCES
    ${ENGINE_DIR}/core/src/engine.cpp
    ${ENGINE_DIR}/core/src/window.cpp
    ${ENGINE_DIR}/core/src/logger.cpp
    ${ENGINE_DIR}/renderer/src/renderer.cpp
    ${ENGINE_DIR}/renderer/src/shader.cpp
    ${ENGINE_DIR}/renderer/src/graphics2d.cpp
    ${ENGINE_DIR}/input/src/input_manager.cpp
    ${ENGINE_DIR}/audio/src/audio_system.cpp
    ${ENGINE_DIR}/physics/src/physics_system.cpp
)

# Build engine as a library
add_library(aurivia_engine ${ENGINE_SOURCES})
target_link_libraries(aurivia_engine PUBLIC OpenGL::OpenGL glfw)

# Editor executable
add_executable(aurivia_editor
    ${EDITOR_DIR}/main.cpp
    ${EDITOR_DIR}/ui/editor_ui.cpp
)
target_link_libraries(aurivia_editor PRIVATE aurivia_engine)

# Sample: Cube Demo
add_executable(cube_demo
    ${SAMPLES_DIR}/cube_demo/main.cpp
)
target_link_libraries(cube_demo PRIVATE aurivia_engine)

# Installation targets
install(TARGETS aurivia_engine DESTINATION lib)
install(TARGETS aurivia_editor DESTINATION bin)
