#include <stdio.h>
#include "board.h"
#include "../utils/ui.h"

GameTile gameTiles[] = {
  {0, 0, EMPTY},
  {0, 1, EMPTY},
  {0, 2, QUESTION},
  {0, 3, EMPTY},
  {1, 3, EMPTY},
  {2, 3, EMPTY},
  {3, 3, EMPTY},
  {3, 4, EMPTY},
};

void drawGameTile(int number) {
  int new_x = gameTiles[number].y * 5 + 1;
  int new_y = gameTiles[number].x * 2 + 1;

  moveCursor(new_x, new_y);
  printf("| %2d |", number+1);
  moveCursor(new_x, new_y + 1);
  printf("|    |");
}

void drawBoard(){
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
