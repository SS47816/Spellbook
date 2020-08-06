cmake_minimum_required(VERSION 3.10)

# set the project name
project(uv)

# specify the C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CXX_FLAGS "-std=c++17 -Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

add_executable(uv src/Wall.cpp src/UVTube.cpp src/main.cpp)