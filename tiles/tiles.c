#include <stdio.h>
#include "tiles.h"
#include "../utils/ui.h"

Tile tiles[8] = {
  {0, 0, EMPTY},
  {0, 1, EMPTY},
  {0, 2, QUESTION},
  {0, 3, EMPTY},
  {1, 3, EMPTY},
  {2, 3, EMPTY},
  {3, 3, EMPTY},
  {3, 4, EMPTY},
};

void drawTile(int number) {
  int new_x = tiles[number].y * 5 + 1;
  int new_y = tiles[number].x * 2 + 1;

  moveCursor(new_x, new_y);
  printf("| %d. |", number+1);
  moveCursor(new_x, new_y + 1);
  printf("|    |");
}

// get the position of a tile given its number
void getTilePosition(int tileNumber, int* x, int* y) {
  // convert tile number to zero-indexed array index
  tileNumber -= 1;

  // calculate x and y position of tile
  *x = tiles[tileNumber].x;
  *y = tiles[tileNumber].y;
}
