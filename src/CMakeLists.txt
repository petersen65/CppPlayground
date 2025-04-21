# CMakeList.txt : CMake project for the src directory, include source and define project specific logic here.
cmake_minimum_required(VERSION 4.0)

# Status messages for important global definitions
message(STATUS "C++ Playground")
message(STATUS "Using source path ${CMAKE_CURRENT_SOURCE_DIR}")

# Search for required packages
find_package(Threads MODULE REQUIRED)

# Declare targets, source files, and dependencies
set(TARGET_APPLICATION "cpp_playground")
set(SOURCECODE_FILES "Playground.cpp" "Distance.cpp")
set(DEPENDENCIES "Threads::Threads" "acciflib")

# Main executable that contains the binary target
add_executable(${TARGET_APPLICATION} ${SOURCECODE_FILES})
target_include_directories(${TARGET_APPLICATION} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${TARGET_APPLICATION} PRIVATE ${DEPENDENCIES})
