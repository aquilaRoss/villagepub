
target_include_directories(commonSource PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(commonSource PRIVATE 
    logger.cpp
    raylibLogging.cpp
)
