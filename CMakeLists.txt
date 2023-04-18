cmake_minimum_required(VERSION 3.24)
set(CMAKE_OSX_ARCHITECTURES x86_64)
project(SFML_CLion)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(/usr/local/include)
#include_directories(${SFML_INCLUDE_DIRS})

find_package(SFML 2.5.1 COMPONENTS REQUIRED audio system window graphics network )
add_subdirectory(src)