cmake_minimum_required(VERSION 3.25)
project(CPPP LANGUAGES CXX)

# Use C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Recursively collect all .cpp files under src/
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable from all sources
add_executable(CPPP ${SOURCES})
