cmake_minimum_required(VERSION 3.15)  # Lowered for better compatibility
project(RayTracer LANGUAGES CXX)      # Explicitly set language

# Set executable output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

# PROPER way to set target-specific flags
target_compile_options(${PROJECT_NAME} PRIVATE
    -g
    -Wall
    -pedantic-errors
    -Werror
    -std=c++23
)

# Add this to find your headers
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/libs
)