cmake_minimum_required(VERSION 3.28)
project(CMPT225FinalProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# To build: `cmake -S . -B build`
# Then: `cmake --build build`
# To test: `cd build && ctest`

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Adding Tests
enable_testing()
add_executable(
  avl_test
  tests/avl_test.cc
  src/avl_tree.cpp
)
target_link_libraries(
  avl_test
  GTest::gtest_main
)
target_include_directories(
  avl_test
  PRIVATE
    include
    ${gtest_SOURCE_DIR}/include
)
include(GoogleTest)
gtest_discover_tests(avl_test)

# Adding Program

include_directories(include)

add_executable(benchmark src/skip_list.cpp src/avl_tree.cpp src/main.cpp)

target_compile_options(benchmark PUBLIC -O3)
