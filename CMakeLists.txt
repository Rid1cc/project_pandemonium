cmake_minimum_required(VERSION 3.29)
project(pandemonium)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

file(GLOB SOURCES
    # sources
    src/*.cpp
    src/*.h
    src/**/*.cpp
    src/**/*.h
    src/***/*.cpp
    src/***/*.h
)

if(WIN32)
    # Define the directory to store the compiler
    set(WINDOWS_TOOLCHAIN_DIR "${CMAKE_BINARY_DIR}/.windows")

    # Check if MinGW-w64 is already available
    find_program(MINGW_W64_GCC_EXECUTABLE gcc.exe PATHS "${WINDOWS_TOOLCHAIN_DIR}/mingw-w64/bin" NO_DEFAULT_PATH)

    if(NOT MINGW_W64_GCC_EXECUTABLE)
        # Create the .windows directory if it doesn't exist
        file(MAKE_DIRECTORY "${WINDOWS_TOOLCHAIN_DIR}/mingw-w64")

        # Define the URL for the MinGW-w64 pre-built archive
        set(MINGW_W64_URL "https://github.com/mingw-w64/mingw-w64/releases/download/release/mingw-w64-release.tar.xz")

        # Define the download path
        set(MINGW_W64_ARCHIVE "${WINDOWS_TOOLCHAIN_DIR}/mingw-w64-release.tar.xz")

        # Download the MinGW-w64 archive
        message(STATUS "Downloading MinGW-w64 toolchain...")
        file(DOWNLOAD ${MINGW_W64_URL} ${MINGW_W64_ARCHIVE} SHOW_PROGRESS)

        # Extract the archive
        message(STATUS "Extracting MinGW-w64 toolchain...")
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xJf ${MINGW_W64_ARCHIVE} --strip-components=1 -C "${WINDOWS_TOOLCHAIN_DIR}/mingw-w64"
            RESULT_VARIABLE extract_result
        )

        if(extract_result EQUAL 0)
            message(STATUS "MinGW-w64 toolchain downloaded and extracted successfully.")
        else()
            message(FATAL_ERROR "Failed to extract MinGW-w64 toolchain.")
        endif()

        # Set the compiler paths
        set(CMAKE_C_COMPILER "${WINDOWS_TOOLCHAIN_DIR}/mingw-w64/bin/gcc.exe")
        set(CMAKE_CXX_COMPILER "${WINDOWS_TOOLCHAIN_DIR}/mingw-w64/bin/g++.exe")

    else()
        message(STATUS "Found existing MinGW-w64 compiler at ${MINGW_W64_GCC_EXECUTABLE}")
    endif()

    # Add the MinGW-w64 bin directory to the PATH
    set(ENV{PATH} "${WINDOWS_TOOLCHAIN_DIR}/mingw-w64/bin;$ENV{PATH}")

    # Find Raylib
    find_package(raylib CONFIG REQUIRED)
    target_link_libraries(pandemonium PRIVATE raylib)

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

elseif(UNIX)
    add_executable(pandemonium ${SOURCES})
    find_package(raylib CONFIG REQUIRED)
    target_link_libraries(pandemonium PRIVATE raylib)

elseif(WIN32)
    add_executable(pandemonium WIN32 ${SOURCES})
    target_link_libraries(pandemonium PRIVATE raylib)
endif()


