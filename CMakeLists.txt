cmake_minimum_required(VERSION 3.16)
project(PICasso)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directory
include_directories(${CMAKE_SOURCE_DIR}/header)

# --- Bibliothek aus src ---
file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_library(MyMemoryLib STATIC ${PROJECT_SOURCES})
target_include_directories(MyMemoryLib PUBLIC ${CMAKE_SOURCE_DIR}/header)

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
target_link_libraries(AllTests PRIVATE MyMemoryLib Catch2::Catch2)
target_include_directories(AllTests PRIVATE ${CMAKE_SOURCE_DIR}/header)

# --- CTest aktivieren ---
enable_testing()
add_test(NAME AllTests COMMAND $<TARGET_FILE:AllTests>)


# --- Executable für das Hauptprogramm ---
add_executable(PICasso src/main.cpp)
target_link_libraries(PICasso PRIVATE MyMemoryLib)
target_include_directories(PICasso PRIVATE ${CMAKE_SOURCE_DIR}/header)

