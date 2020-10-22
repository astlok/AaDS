cmake_minimum_required(VERSION 3.16)

set(PROJECT_SOURCE_FILES ../src/D_Array.cpp)

include_directories(../src)

add_executable(tests test.cpp)

target_link_libraries(tests ${GTEST_LIBRARIES} pthread)
