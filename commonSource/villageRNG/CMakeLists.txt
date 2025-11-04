
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE 
    villageRNG_Implimentation.cpp
    villageRNG_Interface.cpp
)
