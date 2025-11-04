cmake_minimum_required(VERSION 3.15)
project(MyGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_CHILD_PROJECTS "Build child projects" OFF)
option(BUILD_TESTS "Build unit tests" OFF)

include(cmake/BuildRaylib.cmake)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

add_subdirectory(src)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "${RAYLIB_ROOT}/include")
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE "${RAYLIB_ROOT}/lib")
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE 
    raylib
    opengl32
    gdi32
    winmm
    shell32
    user32
)
