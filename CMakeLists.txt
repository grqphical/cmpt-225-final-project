cmake_minimum_required(VERSION 3.28)
project(CMPT225FinalProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_executable(benchmark src/benchmark.cpp src/skip_list.cpp src/balanced_tree.cpp src/main.cpp)
