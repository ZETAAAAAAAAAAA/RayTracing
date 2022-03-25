cmake_minimum_required(VERSION 3.16)
project(myEngine)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)

include_directories(/usr/local/include ./include)

add_executable(test myRayTracing.cpp OBJ_Loader.h Triangle.hpp Render.hpp Render.cpp Texture.hpp)
target_link_libraries(test ${OpenCV_LIBRARIES})