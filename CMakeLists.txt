cmake_minimum_required(VERSION 3.5)
project(games)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(tictactoe src/tictactoe/main.c)

add_executable(test_tictactoe test/test_tictactoe.c)
