cmake_minimum_required(VERSION 3.16)
project(myEngine)

set(CMAKE_CXX_STANDARD 14)

include_directories(ext)

add_executable(test myRayTracing.cpp Rasterizer.hpp Rasterizer.cpp )