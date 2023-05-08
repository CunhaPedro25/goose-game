#include <stdio.h>
#include "board.h"
#include "../utils/ui.h"
#include "terrain.h"

GameTile gameTiles[] = {
  {0, 0, BOOL},
  {0, 1, MULTIPLE},
  {0, 2, MULTIPLE},
  {0, 3, BOOL},
  {1, 3, MULTIPLE},
  {2, 3, BOOL},
  {3, 3, BOOL},
  {3, 4, END},
};

void drawGameTile(int number) {
  int new_x = gameTiles[number].y * 6 + 1;
  int new_y = gameTiles[number].x * 3 + 1;

  setBackgroundColor(gameTiles[number].type, 0);
  moveCursor(new_x, new_y);
  printf("| %2d |", number + 1);
  moveCursor(new_x, new_y + 1);
  printf("|    |");
  moveCursor(new_x, new_y + 2);
  printf("------");
  resetColor();
}

void drawBoard(){
  drawTerrain(10);

  for(int i = 0; i < sizeof(gameTiles)/sizeof(gameTiles[0]); i++){
    drawGameTile(i);
  }
}

// get the position of a tile given its number
void getGameTilePosition(int tileNumber, int* x, int* y) {
  // convert tile number to zero-indexed array index
  tileNumber -= 1;

  // calculate x and y position of tile
  *x = gameTiles[tileNumber].x;
  *y = gameTiles[tileNumber].y;
}


int getGameTileType(int tileNumber) {
  // convert tile number to zero-indexed array index
  tileNumber -= 1;

  // return the type of the tile
  return gameTiles[tileNumber].type;
}
