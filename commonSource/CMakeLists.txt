
# Add the Common Source as a Library so that the unit tests can link against it.
add_library(commonSource STATIC)

target_include_directories(commonSource PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(GRand)
add_subdirectory(Logging)
add_subdirectory(villageRNG)

target_include_directories(commonSource PUBLIC "${RAYLIB_ROOT}/include")
target_link_directories(commonSource PUBLIC "${RAYLIB_ROOT}/lib")

target_link_libraries(commonSource PUBLIC 
    raylib
    opengl32
    gdi32
    winmm
    shell32
    user32
)