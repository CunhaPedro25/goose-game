#ifndef TILES_H
#define TILES_H

#include <stdio.h>
#include <math.h>

#include "terrain.h"
#include "../utils/functions/functions.h"
#include "../utils/ui/ui.h"

typedef enum{
  END = BLUE,
  TRUEFALSE = YELLOW,
  MULTIPLE = MAGENTA,
  WRITTEN = CYAN
}gameTileType;

typedef struct gameTile {
  int x;
  int y;
  gameTileType type;
} GameTile;

void drawBoard();

void getGameTilePosition(int tileNumber, int* x, int* y);
int getGameTileType(int tileNumber);
int getEndTilePosition(int *x, int *y);
int getBoardMaxHeight();
int getBoardMaxWidth();
int getBoardLength();

void writeOnBoardCenter(char* lines[], int numLines);

#endif
