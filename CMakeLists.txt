cmake_minimum_required(VERSION 3.24)
project(SFML_Tetris)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

find_package(SFML 2.5.1 COMPONENTS REQUIRED audio system window graphics network )
add_subdirectory(src)