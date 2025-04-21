# CMakeList.txt : Top-level CMake project file, do global configuration and include sub-projects here.
cmake_minimum_required(VERSION 4.0)

# Needs to be done before project
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH $ENV{HOME}/.local/${CMAKE_BUILD_TYPE})

# Project configuration and description
project(
  "C++"
  DESCRIPTION "C++ Playground"
  LANGUAGES C CXX)

message(STATUS ${PROJECT_DESCRIPTION})

# Compiler options for LLVM Clang, Apple Clang and all other GNU Compiler Collection like compilers
set(BUILD_SHARED_LIBS FALSE)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  add_compile_options(-Wall -Wextra -pedantic -ferror-limit=5 -ftemplate-backtrace-limit=5)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  add_compile_options(-Wall -Wextra -pedantic -ferror-limit=5 -ftemplate-backtrace-limit=5)
else()
  add_compile_options(-Wall -Wextra -pedantic -fmax-errors=5)
endif()

# Determine number of CPU cores
include(ProcessorCount REQUIRED)
ProcessorCount(NPROC)

# Status messages for important global definitions
message(STATUS "Using source path ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "Using module path for module search mode ${CMAKE_MODULE_PATH}")
message(STATUS "Using prefix path for config search mode ${CMAKE_PREFIX_PATH}")
message(STATUS "Using build type ${CMAKE_BUILD_TYPE}")
message(STATUS "Building unit tests ${BUILD_TESTING}")
message(STATUS "Building shared libraries ${BUILD_SHARED_LIBS}")
message(STATUS "Using C++ standard ${CMAKE_CXX_STANDARD}")
message(STATUS "Using C++ extensions ${CMAKE_CXX_EXTENSIONS}")
message(STATUS "Using C++ required standard ${CMAKE_CXX_STANDARD_REQUIRED}")
message(STATUS "Using C++ compiler ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Using CPU architecture ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS "Number of CPU cores ${NPROC}")
message(STATUS "Operating system name ${CMAKE_HOST_SYSTEM_NAME}")

# Include sub-projects
add_subdirectory("src/account")
add_subdirectory("src")

# Include test-packages and configure unit tests
if(${BUILD_TESTING})
  include(CTest)
  include(GoogleTest)
  enable_testing()
  add_subdirectory("test")
endif()
