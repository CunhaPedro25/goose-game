#ifndef TILES_H
#define TILES_H

typedef enum{
  EMPTY,
  QUESTION,
}gameTileType;

typedef struct gameTile {
  int x;
  int y;
  gameTileType type;
} GameTile;

void drawBoard();
void getGameTilePosition(int tileNumber, int* x, int* y);

#endif
