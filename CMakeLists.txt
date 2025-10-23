cmake_minimum_required(VERSION 3.16)
project(MyProject LANGUAGES CXX)

# Use C++17 (adjust as needed)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directory
include_directories(${CMAKE_SOURCE_DIR}/headers)

# Gather all .cpp files from ./src
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Define executable
add_executable(${PROJECT_NAME} ${SRC_FILES})
