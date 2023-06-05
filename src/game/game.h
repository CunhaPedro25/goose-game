#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "../utils/ui/ui.h"
#include "../utils/functions/functions.h"
#include "../board/board.h"
#include "../questions/questions.h"
#include "../player/player.h"

typedef struct game{
  int numberOfPlayers;
  Player players[4];
  char date[80];
}Games;

void getAllGames(Games* games, int maxGames);
void getGameInfo(Games* game, int id);
int getMaxGamesSaved();

void gameLoop();

#endif
