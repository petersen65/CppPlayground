# CMakeList.txt : CMake project for the account directory, include source and define project specific logic here.
cmake_minimum_required(VERSION 4.0)

# Status messages for important global definitions
message(STATUS "Account Library")
message(STATUS "Using source path ${CMAKE_CURRENT_SOURCE_DIR}")

# Search for required packages
find_package(Threads MODULE REQUIRED)
find_package(GTest MODULE REQUIRED)

# Declare targets, source files, and dependencies
set(TARGET_INTERFACE_LIBRARY "acciflib")

set(TARGET_LIBRARY "acclib")
set(SOURCECODE_FILES "Account.cpp")
set(DEPENDENCIES "Threads::Threads")

set(TARGET_TEST_LIBRARY "acctestlib")
set(SOURCECODE_TEST_FILES "test/AccountTest.cpp")
set(TEST_DEPENDENCIES "GTest::gtest" "GTest::gmock")

# Interface
add_library(${TARGET_INTERFACE_LIBRARY} INTERFACE)
target_include_directories(${TARGET_INTERFACE_LIBRARY} INTERFACE "interface")

# Library
add_library(${TARGET_LIBRARY} ${SOURCECODE_FILES})
target_link_libraries(${TARGET_LIBRARY} PUBLIC ${TARGET_INTERFACE_LIBRARY})
target_link_libraries(${TARGET_LIBRARY} PRIVATE ${DEPENDENCIES})

# Test
if(${BUILD_TESTING})
  add_library(${TARGET_TEST_LIBRARY} OBJECT ${SOURCECODE_TEST_FILES})
  target_link_libraries(${TARGET_TEST_LIBRARY} PRIVATE ${TARGET_LIBRARY} ${TEST_DEPENDENCIES})
endif()
