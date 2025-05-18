# CMakeList.txt : CMake project for the worker directory, include source and define project specific logic here.
cmake_minimum_required(VERSION 4.0)

# Status messages for important global definitions
message(STATUS "Worker Library")
message(STATUS "Using source path ${CMAKE_CURRENT_SOURCE_DIR}")

# Search for required packages
find_package(GTest MODULE REQUIRED)

# Declare targets, source files, and dependencies
set(TARGET_INTERFACE_LIBRARY "worker_iflib")

set(TARGET_TEST_LIBRARY "worker_testlib")
set(SOURCECODE_TEST_FILES "test/WorkerTest.cpp")
set(TEST_DEPENDENCIES "core_iflib")
get_target_property(GTEST_INCLUDE_DIRECTORIES "GTest::gtest" INTERFACE_INCLUDE_DIRECTORIES)

# Interface
add_library(${TARGET_INTERFACE_LIBRARY} INTERFACE)
target_include_directories(${TARGET_INTERFACE_LIBRARY} INTERFACE "interface")

# Test
if(${BUILD_TESTING})
  add_library(${TARGET_TEST_LIBRARY} OBJECT ${SOURCECODE_TEST_FILES})
  target_include_directories(${TARGET_TEST_LIBRARY} PRIVATE ${GTEST_INCLUDE_DIRECTORIES})
  target_link_libraries(${TARGET_TEST_LIBRARY} PRIVATE ${TARGET_INTERFACE_LIBRARY} PRIVATE ${TEST_DEPENDENCIES})
endif()
