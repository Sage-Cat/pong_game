cmake_minimum_required(VERSION 3.10)
project(pong_game VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(glfw3)
find_package(glew)
find_package(glm)

# Set global output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include subdirectories
add_subdirectory(src)
# add_subdirectory(test)
