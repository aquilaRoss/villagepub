# CMake and MinGW (If needed)

Check if they are needed with

g++ --version
cmake --version

## If you don't have them, something like this

Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
irm get.scoop.sh | iex
scoop install mingw cmake

### Then check again with the commands from before

# Clone Raylib and googletest
git clone --branch 5.5 --depth 1 https://github.com/raysan5/raylib.git raylib
git clone --branch v1.17.0 --depth 1 https://github.com/google/googletest.git tests/googletest

# Build App
mkdir build && cd build
cmake -G "MinGW Makefiles" -DBUILD_TESTS=ON ..
cmake --build .

## Execute the tests

from the build dir (or if in VSCode Ctrl+Shift+P -> Run Task -> Run Tests)

.\tests\RNGTests.exe