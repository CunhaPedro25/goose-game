#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "../utils/ui.h"
#include "../board/board.h"
#include "../questions/questions.h"
#include "../player/player.h"

void gameLoop(int numPlayers);

#endif
