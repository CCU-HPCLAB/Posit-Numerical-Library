cmake_minimum_required(VERSION 3.14)
project(PositWrapper LANGUAGES CXX)

if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  cmake_minimum_required(VERSION 3.15)
  project(positWrapper)
  set(CMAKE_BUILD_TYPE Release)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED True)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

set(UNIVERSAL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/universal/include)

find_package(pybind11 REQUIRED)

# Set directories
# set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
# set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
# set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

# Add subdirectories
# add_subdirectory(${SRC_DIR})

# Add the library
add_library(positWrapperC SHARED src/positWrapperC.cpp)
add_library(positWrapperPy MODULE src/positWrapperPybind.cpp)

set_target_properties(positWrapperC PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(positWrapperPy PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(positWrapperC PUBLIC ${UNIVERSAL_INCLUDE} ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(positWrapperPy PRIVATE ${UNIVERSAL_INCLUDE} ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(positWrapperPy pybind11::module)

if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    install(TARGETS positWrapperC LIBRARY DESTINATION lib)
    install(TARGETS positWrapperPy LIBRARY DESTINATION lib)

    # install headers
    install(DIRECTORY ${UNIVERSAL_INCLUDE}/ DESTINATION include)
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)

    # add_subdirectory(${TEST_DIR})

    add_executable(test_posit test/test.cpp)
    add_executable(test_math test/test_math.cpp)

    target_link_libraries(test_posit PRIVATE positWrapperC)
    target_link_libraries(test_math PRIVATE positWrapperC)
endif()