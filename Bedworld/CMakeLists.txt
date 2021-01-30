cmake_minimum_required(VERSION 3.15)
project(minecraft)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_definitions(-DGLM_FORCE_XYZW_ONLY)

add_subdirectory(fmt)
add_subdirectory(stl)
add_subdirectory(json)
add_subdirectory(range-v3)
add_subdirectory(glm)

set(CMAKE_CXX_STANDARD 20)

add_library(bedworld blocktable.hpp world.hpp world.cpp)