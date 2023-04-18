file(GLOB SOURCE_FILES "*.cpp" "*.h")

add_executable(SFML_CLion ${SOURCE_FILES})
target_link_libraries(SFML_CLion sfml-system sfml-window sfml-graphics sfml-audio sfml-network)