# VillagePub - Project Instructions for Claude

## Project Overview
A C++ game project using **Raylib** (v5.5) for graphics and **GoogleTest** (v1.17.0) for unit testing.
Built with CMake. Targets Windows (MinGW) and Linux.

## Build System
- **CMake** with `-DBUILD_TESTS=ON` to include tests
- **Windows**: uses `-G "MinGW Makefiles"` generator
- **Linux**: uses default Unix Makefiles generator
- Raylib is cloned locally into `raylib/` and built via `cmake/BuildRaylib.cmake`
- GoogleTest is cloned into `tests/googletest/`
- Neither dependency is committed — they are fetched fresh in CI

## Project Structure
- `main/` — game entry point
- `commonSource/` — shared libraries (villageRNG, Logging, GRand)
- `tests/` — GoogleTest unit tests (RNGTests)
- `cmake/` — CMake helper scripts
- `.github/workflows/` — CI pipelines (Windows + Linux)
- `.vscode/` — VSCode tasks and launch config

## Key Conventions
- C++17 standard
- Test executable is `build/tests/RNGTests.exe` (Windows) or `build/tests/RNGTests` (Linux)
- Test output format: JUnit XML via `--gtest_output=xml:...`
- CI uses `dorny/test-reporter@v2` to publish test results

## Building Locally (Claude-specific)
Claude cannot run the build — the MinGW compiler chain silently fails when invoked from the bash environment Claude uses.

To build and test, ask the human to run the VSCode tasks:
- **Ctrl+Shift+P → "Tasks: Run Task" → "Build MyGame"** — configures and builds
- **Ctrl+Shift+P → "Tasks: Run Task" → "Run Tests"** — builds then runs `RNGTests.exe`

Or from a PowerShell/cmd terminal (not Git Bash):
```
mkdir build
cd build
cmake -G "MinGW Makefiles" -DBUILD_TESTS=ON ..
cmake --build .
.\tests\RNGTests.exe
```

## CI Smoke Test Notes
- Linux smoke test works via `xvfb-run` (Mesa software rendering provides OpenGL)
- Windows smoke test works by copying all Mesa3D x64 DLLs into `build\` before running — this provides software OpenGL since the CI runner has no GPU driver
- Mesa3D is downloaded from `github.com/pal1000/mesa-dist-win` as a `.7z` and all `x64\*.dll` files are copied alongside the exe
- Smoke test is toggleable via `SMOKE_TEST` env var or the `smoke_test` input on manual dispatch

## Things to Keep in Mind
- `cmake/BuildRaylib.cmake` must remain platform-aware (no hardcoded generators)
- Linux CI installs only confirmed-needed packages: `libgl1-mesa-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libasound2-dev` — add more only if the pipeline fails with a specific missing dependency
- The game artifact on Windows is `MyGame.exe`, on Linux it is `MyGame`

## Areas We Are Still Setting Up
- [ ] Anything else to add here — let me know!
