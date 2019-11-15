cmake_minimum_required(VERSION 3.13)
project(OpenCvStereoFPS)
find_package(OpenCV REQUIRED)
find_package(Threads)
set(CMAKE_CXX_STANDARD 17)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")
add_executable(OpenCvStereoFPS main.cpp)

target_link_libraries(OpenCvStereoFPS ${OpenCV_LIBS})
target_link_libraries(OpenCvStereoFPS ${CMAKE_THREAD_LIBS_INIT})
