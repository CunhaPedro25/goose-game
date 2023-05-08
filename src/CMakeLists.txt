cmake_minimum_required(VERSION 3.23)
project(goose-game)

set(CMAKE_C_STANDARD 23)

add_executable(goose-game main.c utils/ui.c utils/functions.c player/player.c board/board.c board/terrain.c)