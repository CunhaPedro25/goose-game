#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>

#include "../utils/ui.h"
#include "../board/board.h"

typedef struct player {
  int color;
  char name[100];
  int currentTile;
} Player;

char *getPlayerName(int id);
int playerCurrentTile(int id);

void drawPlayer(int id, int tile);

#endif
