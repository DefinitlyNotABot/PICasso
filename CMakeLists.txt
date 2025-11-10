cmake_minimum_required(VERSION 3.16)
project(PICasso LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Gather all .cpp files from ./src
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Define executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Get all subdirectories within the 'header' directory
file(GLOB_RECURSE HEADER_SUBDIRS
    LIST_DIRECTORIES true
    RELATIVE ${CMAKE_SOURCE_DIR}/header
    ${CMAKE_SOURCE_DIR}/header/*
)

# Prepend the full path to the found subdirectories
set(FULL_HEADER_SUBDIRS "")
foreach(subdir ${HEADER_SUBDIRS})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/header/${subdir})
        list(APPEND FULL_HEADER_SUBDIRS ${CMAKE_SOURCE_DIR}/header/${subdir})
    endif()
endforeach()

# Use target_include_directories for modern CMake
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/header
        ${CMAKE_SOURCE_DIR}/external/unordered_dense
        # Add all subdirectories found
        ${FULL_HEADER_SUBDIRS}
)
