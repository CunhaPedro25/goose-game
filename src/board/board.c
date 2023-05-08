#include <stdio.h>
#include "board.h"
#include "../utils/ui.h"
#include "terrain.h"

GameTile gameTiles[] = {
  {0, 0, BOOL},
  {1, 0, MULTIPLE},        
  {2, 0, WRITTEN},
  {3, 0, BOOL},
  {3, 1, MULTIPLE},
  {3, 2, BOOL},
  {3, 3, BOOL},
  {4, 3, WRITTEN},
  {5, 3, BOOL},
  {6, 3, BOOL},
  {7, 3, WRITTEN},
  {8, 3, BOOL},
  {9, 3, BOOL},
  {10, 3, BOOL},
  {10, 4, BOOL},
  {10, 5, MULTIPLE},
  {10, 6, BOOL},
  {9, 6, MULTIPLE},
  {8, 6, BOOL},
  {7, 6, WRITTEN},
  {6, 6, END}
};

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

int getEndTilePosition(int *x, int *y){
  int endTile = (sizeof(gameTiles)/sizeof(GameTile))-1;

  *x = gameTiles[endTile].x;
  *y = gameTiles[endTile].y;

  return endTile;
}


void drawGameTile(int number) {
  int new_x = gameTiles[number].x * 6 + 1;
  int new_y = gameTiles[number].y * 3 + 1;

  setBackgroundColor(gameTiles[number].type, (gameTiles[number].type == END));
  moveCursor(new_x, new_y);
  if(gameTiles[number].type == END){
    printf("|END!|");
  }else{
    printf("| %2d |", number + 1);
  }
  moveCursor(new_x, new_y + 1);
  printf("|    |");
  moveCursor(new_x, new_y + 2);
  printf("------");
  resetColor();
}

void drawBoard(){
  int width = 0;
  int height = 0;

  for (int i = 0; i < sizeof(gameTiles)/sizeof(GameTile); i++) {
    if (gameTiles[i].x > width) {
        width = gameTiles[i].x;
    }
    if (gameTiles[i].y > height) {
        height = gameTiles[i].y;
    }
  } 

  drawTerrain(width+2, height+2);

  for(int i = 0; i < sizeof(gameTiles)/sizeof(gameTiles[0]); i++){
    drawGameTile(i);
  }
}