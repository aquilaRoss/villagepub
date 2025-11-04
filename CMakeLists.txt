cmake_minimum_required(VERSION 3.15)
project(MyGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_CHILD_PROJECTS "Build child projects" OFF)
option(BUILD_TESTS "Build unit tests" OFF)

include(cmake/BuildRaylib.cmake)

add_executable(${CMAKE_PROJECT_NAME} main/main.cpp)

add_subdirectory(commonSource)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE commonSource)