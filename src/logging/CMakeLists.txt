# CMakeList.txt : CMake project for the logging directory, include source and define project specific logic here.
cmake_minimum_required(VERSION 4.0)

# Status messages for important global definitions
message(STATUS "Logging Library")
message(STATUS "Using source path ${CMAKE_CURRENT_SOURCE_DIR}")

# Declare targets, source files, and dependencies
set(TARGET_INTERFACE_LIBRARY "logging_iflib")

# Interface
add_library(${TARGET_INTERFACE_LIBRARY} INTERFACE)
target_include_directories(${TARGET_INTERFACE_LIBRARY} INTERFACE "interface")
