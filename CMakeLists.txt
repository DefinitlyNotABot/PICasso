cmake_minimum_required(VERSION 3.16)
project(PICasso LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Define Common Include Root
# This variable holds the root directory for your public headers.
set(PICASSO_HEADER_ROOT ${CMAKE_SOURCE_DIR}/header)

# 2. Find and Collect All Subdirectories for Recursive Includes
# This section is the fix for headers in subdirectories.
# We will use this list for all targets.
file(GLOB_RECURSE HEADER_SUBDIRS
    LIST_DIRECTORIES true
    RELATIVE ${PICASSO_HEADER_ROOT}
    ${PICASSO_HEADER_ROOT}/*
)

# Create the full list of directories to include (Root + Subdirectories)
set(ALL_HEADER_DIRS ${PICASSO_HEADER_ROOT} ${CMAKE_SOURCE_DIR}/external/unordered_dense)
foreach(subdir ${HEADER_SUBDIRS})
    if(IS_DIRECTORY ${PICASSO_HEADER_ROOT}/${subdir})
        list(APPEND ALL_HEADER_DIRS ${PICASSO_HEADER_ROOT}/${subdir})
    endif()
endforeach()

# --- Bibliothek aus src ---
# NOTE: Avoid file(GLOB_RECURSE) for source files if possible.
file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_library(MyMemoryLib STATIC ${PROJECT_SOURCES})

# Use INTERFACE/PUBLIC to propagate includes automatically.
# Any target linking to MyMemoryLib will automatically get these includes.
target_include_directories(MyMemoryLib PUBLIC
    ${ALL_HEADER_DIRS}
)


# --- Catch2 einbinden ---
include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.10
)
FetchContent_MakeAvailable(catch2)

# --- Tests aus /tests ---
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_SOURCE_DIR}/tests/*.cpp")
add_executable(AllTests ${TEST_SOURCES})

# When linking to MyMemoryLib, the includes are already propagated (PUBLIC/INTERFACE).
# We only link Catch2 privately.
target_link_libraries(AllTests PRIVATE MyMemoryLib Catch2::Catch2)

# If tests need any *additional* private includes, add them here.
# NOTE: The public headers are now automatically included via MyMemoryLib.
# target_include_directories(AllTests PRIVATE ...)

# --- CTest aktivieren ---
enable_testing()
add_test(NAME AllTests COMMAND $<TARGET_FILE:AllTests>)


# --- Executable für das Hauptprogramm ---
find_package(Curses REQUIRED)
find_package(Threads REQUIRED)

add_executable(PICasso src/main.cpp terminal/terminal_ui.cpp)

# Linking MyMemoryLib automatically pulls in the PUBLIC include directories.
target_link_libraries(PICasso PRIVATE MyMemoryLib)
target_link_libraries(PICasso PRIVATE ${CURSES_LIBRARIES} Threads::Threads)
target_include_directories(PICasso PRIVATE ${CURSES_INCLUDE_DIR})

# NOTE: The last target_include_directories block from your original file
# is now redundant because the include paths are already applied to the
# PICasso executable via the MyMemoryLib target.