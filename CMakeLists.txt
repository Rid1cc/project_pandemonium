cmake_minimum_required(VERSION 3.29)

if(WIN32)

    add_definitions(-DNOGDI -DNOMINMAX -DWIN32_LEAN_AND_MEAN)
    set(ENV{PATH} "${MINGW64_BIN_DIR};${MSYS2_BIN_DIR};$ENV{PATH}")
    set(WINDOWS_TOOLCHAIN_DIR "${CMAKE_BINARY_DIR}/.windows")
    set(MSYS2_BASE_DIR "${WINDOWS_TOOLCHAIN_DIR}/msys64")
    set(MSYS2_BIN_DIR "${MSYS2_BASE_DIR}/usr/bin")
    set(MINGW64_BIN_DIR "${MSYS2_BASE_DIR}/mingw64/bin")
    set(MSYS2_URL "https://github.com/msys2/msys2-installer/releases/download/nightly-x86_64/msys2-base-x86_64-latest.tar.xz")
    set(MSYS2_ARCHIVE "${WINDOWS_TOOLCHAIN_DIR}/msys2-base-x86_64-latest.tar.xz")
    set(CMAKE_GENERATOR "MinGW Makefiles" CACHE STRING "Default generator for Windows" FORCE)
    set(RAYLIB_URL "https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_win64_mingw-w64.zip")
    set(RAYLIB_ARCHIVE "${CMAKE_BINARY_DIR}/raylib-5.5_win64_mingw-w64.zip")
    set(RAYLIB_DIR "${CMAKE_BINARY_DIR}/raylib/raylib-5.5_win64_mingw-w64/raylib-5.5_win64_mingw-w64")

    if(NOT EXISTS "${RAYLIB_DIR}/lib/libraylib.a")
        message(STATUS "Raylib precompiled binaries not found. Downloading...")

        # Download Raylib
        file(DOWNLOAD ${RAYLIB_URL} ${RAYLIB_ARCHIVE} SHOW_PROGRESS)

        # Extract Raylib
        message(STATUS "Extracting Raylib...")
        execute_process(
            COMMAND powershell -NoProfile -Command
                "if (-not (Get-Command 7z -ErrorAction SilentlyContinue)) {
                    Write-Error '7-Zip not found. Please install 7-Zip and add it to your PATH.'; exit 1;
                }
                7z x '${RAYLIB_ARCHIVE}' -o'${RAYLIB_DIR}' -aoa;"
            RESULT_VARIABLE extract_result
        )
        if(NOT extract_result EQUAL 0)
            message(FATAL_ERROR "Failed to extract Raylib. Ensure 7-Zip is installed and available in PATH.")
        endif()

        message(STATUS "Raylib extracted successfully.")
    else()
        message(STATUS "Found precompiled Raylib in ${RAYLIB_DIR}.")
    endif()
    set(ENV{PATH} "${RAYLIB_DIR}/lib;$ENV{PATH}")

    if(NOT EXISTS "${MINGW64_BIN_DIR}/gcc.exe")
        message(STATUS "MinGW-w64 compiler not found. Downloading and setting up MSYS2...")

        # Create directories
        file(MAKE_DIRECTORY "${WINDOWS_TOOLCHAIN_DIR}")

        # Download MSYS2
        file(DOWNLOAD ${MSYS2_URL} ${MSYS2_ARCHIVE} SHOW_PROGRESS)

        # Extract MSYS2 using 7-Zip
        message(STATUS "Extracting MSYS2 using 7-Zip...")
        execute_process(
            COMMAND powershell -NoProfile -Command
                "if (-not (Get-Command 7z -ErrorAction SilentlyContinue)) {
                    Write-Error '7-Zip not found. Please install 7-Zip and add it to your PATH.';
                    exit 1;
                }
                7z x '${MSYS2_ARCHIVE}' -o'${WINDOWS_TOOLCHAIN_DIR}' -aoa;
                7z x '${WINDOWS_TOOLCHAIN_DIR}/msys2-base-x86_64-latest.tar' -o'${WINDOWS_TOOLCHAIN_DIR}' -aoa;"
            RESULT_VARIABLE extract_result
        )
        if(NOT extract_result EQUAL 0)
            message(FATAL_ERROR "Failed to extract MSYS2. Ensure 7-Zip is installed and available in PATH.")
        endif()

        # Initialize MSYS2 and install required packages
        message(STATUS "Initializing MSYS2 and installing MinGW-w64 toolchain...")
        message(STATUS "Expected path to mintty.exe: ${MSYS2_BIN_DIR}/mintty.exe")
        execute_process(
            COMMAND powershell -NoProfile -Command
                "Start-Process -FilePath '${MSYS2_BIN_DIR}\\mintty.exe' -ArgumentList '/bin/env MSYSTEM=MINGW64 /bin/bash -lc \"pacman -Sy --noconfirm && pacman -S --noconfirm mingw-w64-x86_64-gcc mingw-w64-x86_64-make\"' -Wait"
            RESULT_VARIABLE pacman_result
            
        )

        if(NOT pacman_result EQUAL 0)
            message(FATAL_ERROR "Failed to initialize MSYS2 or install required packages.")
        endif()

        message(STATUS "MSYS2 setup complete. MinGW-w64 toolchain installed.")
    else()
        message(STATUS "Found existing MinGW-w64 compiler at ${MINGW64_BIN_DIR}/gcc.exe")
    endif()


    # Set compiler paths
    set(CMAKE_C_COMPILER "${MINGW64_BIN_DIR}/gcc.exe" CACHE FILEPATH "" FORCE)
    set(CMAKE_CXX_COMPILER "${MINGW64_BIN_DIR}/g++.exe" CACHE FILEPATH "" FORCE)
    set(CMAKE_MAKE_PROGRAM "${MINGW64_BIN_DIR}/mingw32-make.exe" CACHE FILEPATH "Path to make program" FORCE)
endif()

project(pandemonium LANGUAGES C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

file(GLOB SOURCES
    src/*.cpp
    src/*.h
    src/**/*.cpp
    src/**/*.h
)

if(WIN32)
    add_executable(pandemonium ${SOURCES})
    set(CMAKE_EXE_LINKER_FLAGS "-L${RAYLIB_DIR}/lib -lraylib")
    link_directories("${RAYLIB_DIR}/lib")
    target_link_libraries(pandemonium PRIVATE raylib winmm)
    target_include_directories(pandemonium PRIVATE "${RAYLIB_DIR}/include")
    target_compile_definitions(pandemonium PRIVATE 
    -D_CRT_SECURE_NO_WARNINGS 
    -DNOMINMAX 
    -DWIN32_LEAN_AND_MEAN
    -DWIN32_NO_STATUS
)
elseif(APPLE)
    set(MACOSX_BUNDLE_BUNDLE_NAME "Pandemonium")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.yourcompany.pandemonium")
    set(MACOSX_BUNDLE_ICON_FILE "pandemonium.icns")
    set(MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/Resources/Info.plist")

    add_executable(pandemonium_bundle MACOSX_BUNDLE ${SOURCES})
    add_executable(pandemonium ${SOURCES})

    set_source_files_properties(${CMAKE_SOURCE_DIR}/Resources/pandemonium.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    set_source_files_properties(${CMAKE_SOURCE_DIR}/assets PROPERTIES MACOSX_PACKAGE_LOCATION "/")
    target_sources(pandemonium_bundle PRIVATE ${CMAKE_SOURCE_DIR}/Resources/pandemonium.icns)

    # Copy assets folder for bundle
    add_custom_command(TARGET pandemonium_bundle POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_BUNDLE_DIR:pandemonium_bundle>/Contents/assets
    )

    # Set permissions for assets folder in bundle
    add_custom_command(TARGET pandemonium_bundle POST_BUILD
        COMMAND chmod -R 755 $<TARGET_BUNDLE_DIR:pandemonium_bundle>/Contents/assets
    )

    # Create config folder in bundle
    add_custom_command(TARGET pandemonium_bundle POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_BUNDLE_DIR:pandemonium_bundle>/Contents/config
    )

    # Set permissions for config folder in bundle
    add_custom_command(TARGET pandemonium_bundle POST_BUILD
        COMMAND chmod -R 755 $<TARGET_BUNDLE_DIR:pandemonium_bundle>/Contents/config
    )

    # Copy assets folder for normal executable
    add_custom_command(TARGET pandemonium POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:pandemonium>/assets
    )

    # Set permissions for assets folder in normal executable
    add_custom_command(TARGET pandemonium POST_BUILD
        COMMAND chmod -R 755 $<TARGET_FILE_DIR:pandemonium>/assets
    )
    target_link_libraries(pandemonium_bundle PRIVATE raylib)
    find_package(raylib CONFIG REQUIRED)
    target_include_directories(pandemonium PRIVATE ${raylib_INCLUDE_DIRS})
    target_link_libraries(pandemonium PRIVATE raylib)

elseif(UNIX)
    add_executable(pandemonium ${SOURCES})
    find_package(raylib CONFIG REQUIRED)
    target_link_libraries(pandemonium PRIVATE raylib)
endif()
