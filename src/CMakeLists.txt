# Add the library
add_library(positWrapperC SHARED positWrapperC.cpp)
add_library(positWrapperPy MODULE positWrapperPybind.cpp)

target_include_directories(positWrapperC PUBLIC ${UNIVERSAL_INCLUDE} ${CMAKE_SOURCE_DIR}/include)
target_include_directories(positWrapperPy PRIVATE ${UNIVERSAL_INCLUDE} ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(positWrapperPy pybind11::module)

install(TARGETS positWrapperC LIBRARY DESTINATION lib)
install(TARGETS positWrapperPy LIBRARY DESTINATION lib)

# install headers
install(DIRECTORY ${UNIVERSAL_INCLUDE}/ DESTINATION include)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include)