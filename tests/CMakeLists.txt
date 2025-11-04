# Add GoogleTest from the repo
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest)

# Create test executable
add_executable(RNGTests villageRNGTests.cpp)
target_link_libraries(RNGTests PRIVATE commonSource gtest_main)

# Register tests
include(GoogleTest)
gtest_discover_tests(RNGTests)
