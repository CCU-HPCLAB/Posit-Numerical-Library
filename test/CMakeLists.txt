add_executable(test test.cpp)
add_executable(test_math test_math.cpp)

target_link_libraries(test PRIVATE positWrapperC)
target_link_libraries(test_math PRIVATE positWrapperC)