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
    src/settings_draw.cpp 
    src/settings_update.cpp 
    src/title_draw.cpp
    src/title_update.cpp
    src/MiniGameManager.cpp
    src/minigames/RotatingRectangleGame.cpp
    src/minigames/ConnectWiresGame.cpp
    src/minigames/FinderGame.cpp
    src/minigames/TypeGame.cpp
)

add_executable(pandemonium ${SOURCES})

find_package(raylib CONFIG REQUIRED)
target_link_libraries(pandemonium PRIVATE raylib)