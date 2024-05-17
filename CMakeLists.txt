cmake_minimum_required(VERSION 3.24)

project(Oop-5)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-static")
##set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(DateOut 1-5/CDate.cpp 1-5/CDate.h 1-5/tests/CDateTests.cpp)
add_executable(DateTests 1-5/tests/CDateTests.cpp 1-5/CDate.cpp)


target_link_libraries(DateTests gtest)


add_executable(CMyString 2-1/CMyString.cpp)
add_executable(CMyStringTests 2-1/tests/CMyStringTests.cpp 2-1/CMyString.cpp)

target_link_libraries(CMyStringTests gtest)

