cmake_minimum_required(VERSION 3.16)
project(SnakeSFML LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(snake
    src/main.cpp
    src/graphics/Renderer.cpp
    src/core/Snake.cpp
)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(snake PRIVATE sfml-graphics sfml-window sfml-system)

target_include_directories(snake PRIVATE include)
