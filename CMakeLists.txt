cmake_minimum_required(VERSION 3.29)
project(pandemonium)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

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
    # Managers
    src/managers/MiniGameManager.cpp
    src/managers/EventManager.cpp
    #
    src/minigames/RotatingRectangleGame.cpp
    src/minigames/ConnectWiresGame.cpp
    src/minigames/FinderGame.cpp
)

add_executable(pandemonium ${SOURCES})

find_package(raylib CONFIG REQUIRED)
target_link_libraries(pandemonium PRIVATE raylib)