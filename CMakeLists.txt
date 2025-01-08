cmake_minimum_required(VERSION 3.15)
project(positWrapper)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(UNIVERSAL_INCLUDE ${CMAKE_SOURCE_DIR}/3rd_party/universal/include)

find_package(pybind11 REQUIRED)

# Set directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

# Add subdirectories
add_subdirectory(${SRC_DIR})
add_subdirectory(${TEST_DIR})