
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#target_sources(${CMAKE_PROJECT_NAME} PRIVATE 
#    something.cpp
#)

add_subdirectory(GRand)
add_subdirectory(Logging)
add_subdirectory(villageRNG)