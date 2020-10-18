cmake_minimum_required(VERSION 3.17)
project(zadacha_2_4)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(zadacha_2_4
        src/main.cpp src/nearest_index.cpp include/nearest_index.h)
