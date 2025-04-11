cmake_minimum_required(VERSION 3.24)
project(SFML_Tetris)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#find_package(SFML 2.5.1 COMPONENTS REQUIRED audio system window graphics network )
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
        GIT_SHALLOW ON
        SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB SOURCE_FILES "src/*.cpp" "src/*.h")

add_executable(SFML_Tetris ${SOURCE_FILES})
target_link_libraries(SFML_Tetris PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)