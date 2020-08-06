project(uv)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CXX_FLAGS "-std=c++17 -I/usr/include/python2.7 -lpython2.7 -Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(sources src/Wall.cpp src/UVTube.cpp src/main.cpp)

add_executable(uv ${sources})

#find_package(Python2 COMPONENTS Interpreter Development)
#find_package(PythonLibs 2.7)
#target_include_directories(uv PRIVATE ${PYTHON_INCLUDE_DIRS})
#target_link_libraries(uv ${PYTHON_LIBRARIES})