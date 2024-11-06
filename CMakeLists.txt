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
)

add_executable(pandemonium ${SOURCES})

find_package(raylib CONFIG REQUIRED)
target_link_libraries(pandemonium PRIVATE raylib)