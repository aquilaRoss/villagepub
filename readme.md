# CMake and MinGW (If needed)

Check if they are needed with

g++ --version
cmake --version

## If you don't have them, something like this

Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
irm get.scoop.sh | iex
scoop install mingw cmake

### Then check again with the commands from before

# Get and Build Raylib
git clone https://github.com/raysan5/raylib.git
mkdir raylib/build
cd raylib/build
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../../artifacts/raylib/install ..
cmake --build .
cmake --install . --prefix ../../artifacts/raylib/install
cd ../..

# Build App
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .