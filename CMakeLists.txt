cmake_minimum_required(VERSION 3.15)
project(MyGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RAYLIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/artifacts/raylib/install")

add_executable(MyGame src/main.cpp)

target_include_directories(MyGame PRIVATE "${RAYLIB_ROOT}/include")
target_link_directories(MyGame PRIVATE "${RAYLIB_ROOT}/lib")
target_link_libraries(MyGame PRIVATE 
    raylib
    opengl32
    gdi32
    winmm
    shell32
    user32
)
