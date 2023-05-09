#ifndef TILES_H
#define TILES_H

typedef enum{
  BOOL = 3,
  END = 4,
  MULTIPLE = 5,
  WRITTEN = 6
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

#endif
