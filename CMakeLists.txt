project(BenchSampling)
cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(CPM)
include(googlebenchmark)


add_executable(statDistrib statDistrib.cpp)

add_executable(benchmark-example benchmark-example.cpp)
target_link_libraries(benchmark-example benchmark)

add_executable(benchGenerator benchGenerator.cpp)
target_link_libraries(benchGenerator benchmark)

### Fin du TP
#add_executable(test-test01 test-test01.cpp)
#target_include_directories(test-test01 PRIVATE "${PROJECT_SOURCE_DIR}/testU01/local/include")
#target_link_directories(test-test01 PRIVATE "${PROJECT_SOURCE_DIR}/testU01/local/lib")
#target_link_libraries(test-test01  PRIVATE libtestU01.a libprobdist.a libmylib.a)


add_executable(test-timer test-timer.cpp)
