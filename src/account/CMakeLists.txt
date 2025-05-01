# CMakeList.txt : CMake project for the account directory, include source and define project specific logic here.
cmake_minimum_required(VERSION 4.0)

# Status messages for important global definitions
message(STATUS "Account Library")
message(STATUS "Using source path ${CMAKE_CURRENT_SOURCE_DIR}")

# Search for required packages
find_package(Threads MODULE REQUIRED)
find_package(GTest MODULE REQUIRED)

# Declare targets, source files, and dependencies
set(TARGET_INTERFACE_LIBRARY "account_iflib")

set(TARGET_LIBRARY "accountlib")
set(SOURCECODE_FILES "Account.cpp")
set(DEPENDENCIES "Threads::Threads")

set(TARGET_TEST_LIBRARY "account_testlib")
set(SOURCECODE_TEST_FILES "test/AccountTest.cpp")
set(TEST_DEPENDENCIES "")
get_target_property(GTEST_INCLUDE_DIRECTORIES "GTest::gtest" INTERFACE_INCLUDE_DIRECTORIES)

# Interface
add_library(${TARGET_INTERFACE_LIBRARY} INTERFACE)
target_include_directories(${TARGET_INTERFACE_LIBRARY} INTERFACE "interface")

# Library
add_library(${TARGET_LIBRARY} ${SOURCECODE_FILES})
target_link_libraries(${TARGET_LIBRARY} PUBLIC ${TARGET_INTERFACE_LIBRARY} PRIVATE ${DEPENDENCIES})

# Test
if(${BUILD_TESTING})
  add_library(${TARGET_TEST_LIBRARY} OBJECT ${SOURCECODE_TEST_FILES})
  target_include_directories(${TARGET_TEST_LIBRARY} PRIVATE ${GTEST_INCLUDE_DIRECTORIES})
  target_link_libraries(${TARGET_TEST_LIBRARY} PRIVATE ${TARGET_LIBRARY} PRIVATE ${TEST_DEPENDENCIES})
endif()
