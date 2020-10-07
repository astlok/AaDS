cmake_minimum_required(VERSION 3.17)
project(AaDS)

INCLUDE_DIRECTORIES(include)

set(CMAKE_CXX_STANDARD 14)

add_executable(AaDS src/main.cpp src/max_sum_index.cpp include/max_sum_index.h)