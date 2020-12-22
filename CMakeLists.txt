cmake_minimum_required(VERSION 3.17)
project(AaDS)

set(CMAKE_CXX_STANDARD 14)
include_directories(include)

add_executable(AaDS src/main.cpp src/utils.cpp src/ListGraph.cpp src/MatrixGraph.cpp src/SetGraph.cpp src/ArcGraph.cpp)