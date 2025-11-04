# CMake and MinGW (If needed)

Check if they are needed with

g++ --version
cmake --version

## If you don't have them, something like this

Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
irm get.scoop.sh | iex
scoop install mingw cmake

### Then check again with the commands from before

# Clone Raylib
git clone --branch 5.5 --depth 1 https://github.com/raysan5/raylib.git raylib

# Build App
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .