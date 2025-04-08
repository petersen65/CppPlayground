# CMakeList.txt : CMake project for the src directory, include source and define project specific logic here.
cmake_minimum_required(VERSION 4.0)

# Status messages for important global definitions
message(STATUS "C++ Playground")
message(STATUS "Using source path ${CMAKE_CURRENT_SOURCE_DIR}")

# Search for required packages
find_package(Threads MODULE REQUIRED)

# Declare target, source files, and dependencies
set(TARGET_APPLICATION "cpp_playground")
set(SOURCECODE_FILES "Playground.cpp" "Account.cpp")
set(OTHER_DEPENDENCIES "Threads::Threads")

# Main executable that contains the binary target
add_executable(${TARGET_APPLICATION} ${SOURCECODE_FILES})
target_include_directories(${TARGET_APPLICATION} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${TARGET_APPLICATION} PRIVATE ${OTHER_DEPENDENCIES})

# Install target for the application and its dependencies
install(TARGETS ${TARGET_APPLICATION})
