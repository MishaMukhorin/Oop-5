cmake_minimum_required(VERSION 3.0)

project(Oop-5)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-static")
##set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")

add_subdirectory(lib/googletest)
INCLUDE_DIRECTORIES(gtest lib/googletest/googletest/include)

add_executable(DateOut 1-5/CDate.cpp)
add_executable(DateTests 1-5/tests/CDateTests.cpp 1-5/CDate.cpp)


target_link_libraries(DateTests gtest)

