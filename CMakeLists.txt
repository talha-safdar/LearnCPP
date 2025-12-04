cmake_minimum_required(VERSION 3.10)

project(Syrum)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include folder
include_directories(include)

# Add source files
file(GLOB SOURCES "src/*.cpp")

add_executable(Syrum ${SOURCES})
