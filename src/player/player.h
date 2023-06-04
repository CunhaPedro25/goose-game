#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../utils/ui.h"
#include "../board/board.h"

typedef struct player {
  int color;
  char name[100];
  int currentTile;
} Player;

void createPlayers(int numPlayers);

bool isNameTaken(const char* name, int currentPlayer);
void savePlayerName(int id, char *newName);
bool isColorTaken(int color, int currentPlayer);
void savePlayerColor(int id, int color);

char *getPlayerName(int id);
int playerCurrentTile(int id);

void drawPlayer(int id, int tile);

#endif
