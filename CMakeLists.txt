cmake_minimum_required(VERSION 3.5.0)
project(polynom VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)

include_directories(src tests)

add_library(polynom src/polynom.hpp)
set_target_properties(polynom PROPERTIES LINKER_LANGUAGE CXX)

enable_testing()

add_executable(test_basic tests/test_basic.cpp)
target_link_libraries(test_basic PRIVATE polynom)

add_executable(test_custom tests/test_custom.cpp)
target_link_libraries(test_custom PRIVATE polynom)

add_test(NAME test_basic COMMAND $<TARGET_FILE:test_basic>)
add_test(NAME test_custom COMMAND $<TARGET_FILE:test_custom>)