cmake_minimum_required(VERSION 3.29)
project(pandemonium)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

add_executable(pandemonium main.cpp
        Game/main.hpp)
find_package(raylib CONFIG REQUIRED)
target_link_libraries(pandemonium PRIVATE raylib)

add_subdirectory(Game)