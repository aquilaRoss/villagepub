
target_include_directories(commonSource PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(commonSource PRIVATE 
    villageRNG_Implimentation.cpp
    villageRNG_Interface.cpp
)
