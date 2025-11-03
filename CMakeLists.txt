cmake_minimum_required(VERSION 3.15)
project(MyGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED PLATFORM)
    message(FATAL_ERROR "PLATFORM variable not set. Pass -DPLATFORM=Windows or -DPLATFORM=Android")
endif()

if(PLATFORM STREQUAL "Windows")
    set(RAYLIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/artifacts/raylib/install")
elseif(PLATFORM STREQUAL "Android")
    set(RAYLIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/artifacts/raylib/install")
else()
    message(FATAL_ERROR "Unknown PLATFORM: ${PLATFORM}. Must be Windows or Android")
endif()

add_executable(MyGame src/main.cpp)

target_include_directories(MyGame PRIVATE "${RAYLIB_ROOT}/include")
target_link_directories(MyGame PRIVATE "${RAYLIB_ROOT}/lib")
target_link_libraries(MyGame PRIVATE raylib)

if(PLATFORM STREQUAL "Windows")
    target_link_libraries(MyGame PRIVATE 
        opengl32
        gdi32
        winmm
        shell32
        user32
    )
elseif(PLATFORM STREQUAL "Android")
    target_link_libraries(MyGame PRIVATE 
        log
        android
        GLESv2
        EGL
    )
endif()