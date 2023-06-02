#include "board.h"

GameTile gameTiles[] = {
  {1, 1, BOOL},
  {2, 1, MULTIPLE},
  {3, 1, WRITTEN},
  {4, 1, BOOL},
  {5, 1, MULTIPLE},
  {6, 1, WRITTEN},

  {6, 2, BOOL},
  {6, 3, MULTIPLE},
  {6, 4, WRITTEN},
  {6, 5, BOOL},
  {6, 6, MULTIPLE},
  {6, 7, WRITTEN},

  {5, 7, BOOL},
  {4, 7, MULTIPLE},
  {3, 7, WRITTEN},
  {2, 7, BOOL},
  {1, 7, MULTIPLE},

  {1, 6, WRITTEN},
  {1, 5, BOOL},
  {1, 4, WRITTEN},
  {1, 3, MULTIPLE},

  {2, 3, BOOL},
  {3, 3, MULTIPLE},

  {4, 3, END},
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

int getBoardMaxHeight(){
  int height = 0;

  for (int i = 0; i < sizeof(gameTiles)/sizeof(GameTile); i++) {
    if (gameTiles[i].y > height) {
        height = gameTiles[i].y;
    }
  }

  return height;
}

int getBoardMaxWidth(){
  int width = 0;

  for (int i = 0; i < sizeof(gameTiles)/sizeof(GameTile); i++) {
    if (gameTiles[i].x > width) {
        width = gameTiles[i].x;
    }
  }

  return width;
}

int getEndTilePosition(int *x, int *y){
  int endTile = (sizeof(gameTiles)/sizeof(GameTile))-1;

  *x = gameTiles[endTile].x;
  *y = gameTiles[endTile].y;

  return endTile;
}

int getBoardLength(){
  return sizeof(gameTiles)/sizeof(GameTile);
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
  drawTerrain();

  for(int i = 0; i < sizeof(gameTiles)/sizeof(gameTiles[0]); i++){
    drawGameTile(i);
  }
}
