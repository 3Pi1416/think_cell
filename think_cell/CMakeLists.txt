cmake_minimum_required(VERSION 3.16)
project(think_cell LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_executable(test_interval_map test_interval_map.cpp)
add_test(test_interval_maps test_interval_map)