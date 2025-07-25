# CMakeList.txt : CMake project for the test_package directory, include source and define project specific logic here.
cmake_minimum_required(VERSION 4.0)

# Status messages for important global definitions
message(STATUS "C++ Playground Tests")
message(STATUS "Using source path ${CMAKE_CURRENT_SOURCE_DIR}")

# Search for required packages using MODULE mode
find_package(Threads MODULE REQUIRED)
find_package(GTest MODULE REQUIRED)

# Declare target, source files, and dependencies
set(TARGET_TESTS "cpp_playground_test")
set(SOURCECODE_FILES "")
set(TEST_DEPENDENCIES "GTest::gtest_main" "GTest::gmock" "account_testlib" "worker_testlib")
set(DEPENDENCIES "Threads::Threads")

# Test executable that contains the binary target
add_executable(${TARGET_TESTS} ${SOURCECODE_FILES})
target_link_libraries(${TARGET_TESTS} PRIVATE ${TEST_DEPENDENCIES} ${DEPENDENCIES})

# Automatically add tests to CTest by querying the compiled test executable for available tests
gtest_discover_tests(
  ${TARGET_TESTS}
  EXTRA_ARGS "--gtest_output=json:${CMAKE_BINARY_DIR}/unittest_results/"
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
