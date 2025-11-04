set(RAYLIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/artifacts/raylib/install")

# Check if raylib is already installed
if(NOT EXISTS "${RAYLIB_ROOT}/lib/libraylib.a" AND NOT EXISTS "${RAYLIB_ROOT}/lib/raylib.lib")
    message(STATUS "Raylib not found in artifacts — attempting to build it...")

    # Ensure raylib source exists
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/raylib/CMakeLists.txt")
        message(STATUS "Found local raylib source, configuring and building...")

        # Define a build directory for raylib inside the main build folder
        set(RAYLIB_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/raylib_build")
        file(MAKE_DIRECTORY "${RAYLIB_BUILD_DIR}")
        file(MAKE_DIRECTORY "${RAYLIB_ROOT}")

        execute_process(
            COMMAND ${CMAKE_COMMAND} -G "MinGW Makefiles"
                    -DCMAKE_BUILD_TYPE=Release
                    -DCMAKE_INSTALL_PREFIX=${RAYLIB_ROOT}
                    ${CMAKE_CURRENT_SOURCE_DIR}/raylib
            WORKING_DIRECTORY ${RAYLIB_BUILD_DIR}
            RESULT_VARIABLE CONFIGURE_RESULT
        )

        if(NOT CONFIGURE_RESULT EQUAL 0)
            message(FATAL_ERROR "Raylib configuration failed.")
        endif()

        execute_process(
            COMMAND ${CMAKE_COMMAND} --build . --target install
            WORKING_DIRECTORY ${RAYLIB_BUILD_DIR}
            RESULT_VARIABLE BUILD_RESULT
        )

        if(NOT BUILD_RESULT EQUAL 0)
            message(FATAL_ERROR "Raylib build/install failed.")
        endif()

    else()
        message(FATAL_ERROR "Raylib not found! Please clone https://github.com/raysan5/raylib into the project root.")
    endif()
else()
    message(STATUS "Using existing Raylib from artifacts.")
endif()