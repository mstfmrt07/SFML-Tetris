file(GLOB SOURCE_FILES "*.cpp" "*.h")

add_executable(SFML_Tetris ${SOURCE_FILES})
target_link_libraries(SFML_Tetris sfml-system sfml-window sfml-graphics sfml-audio sfml-network)