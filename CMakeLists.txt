cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

project("tetris")

add_subdirectory(macos)

#include_directories(${PROJECT_SOURCE_DIR}/headers)
target_link_libraries(main ncurses)