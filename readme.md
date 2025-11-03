# Install vcpkg (if not already)
git clone https://github.com/microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat

# Get/setup scoop
Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
irm get.scoop.sh | iex

# CMake and MinGW
scoop install mingw cmake

### You can check this with
g++ --version
cmake --version

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