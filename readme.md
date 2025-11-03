# Windows

## CMake and MinGW (If needed)

Check if they are needed with

g++ --version
cmake --version

### If you don't have them, something like this

Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
irm get.scoop.sh | iex
scoop install mingw cmake

### Then check again with the commands from before

## Get and Build Raylib
git clone https://github.com/raysan5/raylib.git
mkdir raylib/build
mkdir artifacts/raylib/install
cd raylib/build
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../../artifacts/raylib/install ..
cmake --build .
cmake --install . --prefix ../../artifacts/raylib/install
cd ../..

## Build App
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .

# Android

## JDK (Should only need to do this once)

New-Item -ItemType Directory -Force -Path android\java | Out-Null
Invoke-WebRequest -Uri "https://github.com/adoptium/temurin17-binaries/releases/download/jdk-17.0.16%2B8/OpenJDK17U-jdk_x64_windows_hotspot_17.0.16_8.zip" -OutFile "android\java\jdk17.zip"
Expand-Archive "android\java\jdk17.zip" -DestinationPath "android\java\jdk17"

## Download and Install the SDK (Should only need to do this once)

New-Item -ItemType Directory -Force -Path android\sdk | Out-Null
set ANDROID_SDK_ROOT=%CD%\android\sdk
set ANDROID_HOME=%ANDROID_SDK_ROOT%
Invoke-WebRequest https://dl.google.com/android/repository/commandlinetools-win-11076708_latest.zip -OutFile android\sdk\cmdline-tools.zip
Expand-Archive android\sdk\cmdline-tools.zip -DestinationPath android\sdk\cmdline-tools\latest
Move-Item -Path "android\sdk\cmdline-tools\latest\cmdline-tools\*" -Destination "android\sdk\cmdline-tools\latest" 
Remove-Item -Recurse -Force "android\sdk\cmdline-tools\latest\cmdline-tools"
$env:ANDROID_SDK_ROOT = "$PWD\android\sdk"
$env:ANDROID_HOME = $env:ANDROID_SDK_ROOT
$env:PATH = "$env:ANDROID_SDK_ROOT\cmdline-tools\latest\bin;$env:PATH"
mkdir $env:ANDROID_SDK_ROOT/licenses
Copy-Item -Recurse "./licenses/android/sdk/licenses/*" "$env:ANDROID_SDK_ROOT/licenses/"
sdkmanager.bat --sdk_root=%ANDROID_SDK_ROOT% "platform-tools" "ndk;26.3.11579264" "cmake;3.30.5"
$env:PATH = "$env:ANDROID_SDK_ROOT\platform-tools;$env:ANDROID_SDK_ROOT\cmake\3.30.5\bin;$env:ANDROID_SDK_ROOT\ndk\26.3.11579264;$env:PATH"

### Accepting the License

It was hard work, I had to accept them manually, then save the files and hope it worked, I accepted them manulaly doing this

cmd.exe /C "%ANDROID_HOME%\cmdline-tools\latest\bin\sdkmanager.bat --licenses"

from the repo head after the $env:PATH was updated in the above steps then did the inverse of the above mkdir/copy

### Checking it Installed

sdkmanager.bat --list

Scroll to the TOP, it will show the installed stuff first like this

Installed packages:
  Path              | Version       | Description                      | Location
  -------           | -------       | -------                          | -------
  cmake;3.22.1      | 3.22.1        | CMake 3.22.1                     | cmake\3.22.1     
  ndk;26.3.11579264 | 26.3.11579264 | NDK (Side by side) 26.3.11579264 | ndk\26.3.11579264
  platform-tools    | 36.0.0        | Android SDK Platform-Tools       | platform-tools

Can also check like this

adb --version
ndk-build --version
cmake --version

## Get and Build Raylib
git clone https://github.com/raysan5/raylib.git
mkdir raylib/build
mkdir artifacts/raylib/install
cd raylib/build
cmake .. -G "Ninja" -DCMAKE_TOOLCHAIN_FILE="$env:ANDROID_SDK_ROOT/ndk/26.3.11579264/build/cmake/android.toolchain.cmake" -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-24 -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX=$PWD/install -DPLATFORM=Android -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF -DBUILD_GAMES=OFF -DX11=OFF
cmake --build .
cmake --install . --prefix ../../artifacts/raylib/install

## Now the App
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .





