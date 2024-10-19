cmake_minimum_required(VERSION 3.5.0)
project(polynom VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)

add_library(polynom polynom.hpp)
set_target_properties(polynom PROPERTIES LINKER_LANGUAGE CXX)

enable_testing()

add_executable(test_basic test_basic.cpp)
target_link_libraries(test_basic PRIVATE polynom)
target_compile_options(test_basic PRIVATE -coverage)
target_link_options(test_basic PRIVATE -coverage)

add_test(NAME test_basic COMMAND $<TARGET_FILE:test_basic>)