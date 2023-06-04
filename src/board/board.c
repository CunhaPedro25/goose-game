#include "board.h"

GameTile gameTiles[] = {
  {1, 1, TRUEFALSE},
  {2, 1, MULTIPLE},
  {3, 1, WRITTEN},
  {4, 1, TRUEFALSE},
  {5, 1, MULTIPLE},
  {6, 1, WRITTEN},

  {6, 2, TRUEFALSE},
  {6, 3, MULTIPLE},
  {6, 4, WRITTEN},
  {6, 5, TRUEFALSE},
  {6, 6, MULTIPLE},
  {6, 7, WRITTEN},

  {5, 7, TRUEFALSE},
  {4, 7, MULTIPLE},
  {3, 7, WRITTEN},
  {2, 7, TRUEFALSE},
  {1, 7, MULTIPLE},

  {1, 6, WRITTEN},
  {1, 5, TRUEFALSE},
  {1, 4, WRITTEN},
  {1, 3, MULTIPLE},

  {2, 3, TRUEFALSE},
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

  return height+1;  // +1 because terrain always has an extra tile
}

int getBoardMaxWidth(){
  int width = 0;

  for (int i = 0; i < sizeof(gameTiles)/sizeof(GameTile); i++) {
    if (gameTiles[i].x > width) {
        width = gameTiles[i].x;
    }
  }

  return width+1;
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


void writeOnBoardCenter(char* lines[], int numLines) {
  saveCursor();
  int boardHeight = getBoardMaxHeight();
  int boardWidth = (getBoardMaxWidth() + 1) * 6 + 1;
  int startX, startY;

  startY = ((boardHeight - numLines) / 2) * 3 + 1;  // Calculate the starting Y position

  if (startY < 0) {
    startY = 0;
  }

  for (int i = 0; i < numLines; i++) {
    startX = (boardWidth - strlen_utf8(lines[i])) / 2;  // Calculate the starting X position

    if (startX < 0) {
      startX = 0;
    }

    moveCursor(startX+1, (startY + i * 3) + 1);  // Move the cursor to the appropriate position
    printf("%s", lines[i]);  // Print the line of text
  }
  restoreCursor();
  waitInput("Press any key to continue...");
}

