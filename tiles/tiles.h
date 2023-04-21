#ifndef TILES_H
#define TILES_H

enum tileType {
  EMPTY,
  QUESTION,
};

typedef struct tile {
  int x;
  int y;
  int type;
} Tile;

void drawTile(int number);

void getTilePosition(int tileNumber, int* x, int* y);

#endif
