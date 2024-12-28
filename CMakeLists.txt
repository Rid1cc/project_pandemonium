cmake_minimum_required(VERSION 3.29)
project(pandemonium)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

#Enable debugging symbols
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

#Enable Address Sanitizer
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
# Dodanie wszystkich plików źródłowych
set(SOURCES
    src/main.cpp
    src/globals.cpp
    src/gameplay_draw.cpp
    src/gameplay_update.cpp
    src/CommandInterpreter.cpp
    src/shader_handler.cpp
    # settings
    src/settings/settings_vars.cpp
    src/settings/settings_draw.cpp 
    src/settings/settings_update.cpp
    src/settings/sc_audio.cpp
    src/settings/sc_graphics.cpp
    src/settings/sc_display.cpp
    src/settings/sc_custom.cpp
    #
    src/title_draw.cpp
    src/title_update.cpp
    src/MiniGame.cpp
    src/MiniGameManager.cpp
    src/minigames/RotatingRectangleGame.cpp
    src/minigames/ConnectWiresGame.cpp
    src/minigames/FinderGame.cpp
    src/minigames/TypeGame.cpp
# Add your sources
)
file(GLOB SOURCES
    # sources
    src/*.cpp
    src/*.h
    src/**/*.cpp
    src/**/*.h
    src/***/*.cpp
    src/***/*.h
)


if(APPLE)
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
elseif(UNIX)
    add_executable(pandemonium ${SOURCES})
endif()

find_package(raylib CONFIG REQUIRED)
target_link_libraries(pandemonium PRIVATE raylib)
target_link_libraries(pandemonium_bundle PRIVATE raylib)

