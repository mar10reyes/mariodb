cmake_minimum_required(VERSION 3.0)
project(mariodb)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add include directory
include_directories(include)

# Gather all source files
file(GLOB SOURCES "src/*.cpp")

# Add executable
add_executable(program ${SOURCES})
