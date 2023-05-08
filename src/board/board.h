#ifndef TILES_H
#define TILES_H

typedef enum{
  END = 9,
  BOOL = 3,
  MULTIPLE = 4,
  WRITTEN = 5
}gameTileType;

typedef struct gameTile {
  int x;
  int y;
  gameTileType type;
} GameTile;

void drawBoard();
void getGameTilePosition(int tileNumber, int* x, int* y);
int getGameTileType(int tileNumber);

#endif
