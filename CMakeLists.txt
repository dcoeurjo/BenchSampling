project(BenchSampling)
cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(CPM)
include(googlebenchmark)




add_executable(test-timer test-timer.cpp)

add_executable(benchmark-example benchmark-example.cpp)
target_link_libraries(benchmark-example benchmark)

add_executable(bench bench.cpp)
target_link_libraries(bench benchmark)
