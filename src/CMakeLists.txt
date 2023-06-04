cmake_minimum_required(VERSION 3.23)
project(goose-game)

set(CMAKE_C_STANDARD 23)

add_executable(goose-game main.c utils/ui/ui.c utils/functions/functions.c utils/menus/menus.c utils/pages/page.c player/player.c board/board.c board/terrain.c questions/boolAnswer.c questions/multipleChoiceAnswer.c questions/directAnswer.c questions/questions.c game/game.c)
