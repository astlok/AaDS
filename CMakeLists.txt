cmake_minimum_required(VERSION 3.17)
project(AaDS)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

add_executable(AaDS src/main.cpp src/D_Array.cpp src/Heap.cpp src/merge_sort.cpp src/kth_statistic.cpp)
