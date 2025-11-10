cmake_minimum_required(VERSION 3.16)
project(PICasso)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directory
include_directories(${CMAKE_SOURCE_DIR}/headers)

# Gather all .cpp files from ./src
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Define executable
add_executable(${PROJECT_NAME} ${SRC_FILES})



# Projektbibliothek bauen
file(GLOB_RECURSE PROJECT_SOURCES "src/**/*.cpp")
add_library(MyMemoryLib ${PROJECT_SOURCES})
target_include_directories(MyMemoryLib PUBLIC src/header)

# Catch2 über FetchContent einbinden
include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.10
)
FetchContent_MakeAvailable(catch2)

# Alle Testquellen automatisch sammeln
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")

# Test-Binär bauen
add_executable(AllTests ${TEST_SOURCES})
target_link_libraries(AllTests PRIVATE MyMemoryLib Catch2::Catch2)
target_include_directories(AllTests PRIVATE src/header)

# CTest
enable_testing()
add_test(NAME AllTests COMMAND $<TARGET_FILE:AllTests>)
