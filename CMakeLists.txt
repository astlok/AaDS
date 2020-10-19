cmake_minimum_required(VERSION 3.17)
project(zadacha_2_4)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(include)
add_executable(zadacha_2_4 src/main.cpp)

add_subdirectory(tests)