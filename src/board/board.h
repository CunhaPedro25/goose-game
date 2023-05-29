#ifndef TILES_H
#define TILES_H

#include <stdio.h>

#include "../utils/functions.h"
#include "../utils/ui.h"

typedef enum{
  END = BLUE,
  BOOL = YELLOW,
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

#endif
