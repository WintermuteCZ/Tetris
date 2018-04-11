cmake_minimum_required(VERSION 3.5)
project(tetris)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic")

find_package(SDL2 REQUIRED)

# workaround for the trailing whitespace problem
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES Board.cpp Game.cpp IO.cpp Level.cpp main.cpp Score.cpp Tetromino.cpp)

add_executable(tetris ${SOURCE_FILES})
target_link_libraries(tetris ${SDL2_LIBRARIES} SDL2_ttf)