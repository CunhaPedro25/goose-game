#include "board.h"

#define FILE_PATH_LENGTH 256
#define EXTRA_PATH_LENGTH 512

#ifdef _WIN32
    #define PLATFORM_PATH_ENV "LOCALAPPDATA"
    #define PLATFORM_FOLDER "gooseGame\\boards\\"
#elif __linux__
    #define PLATFORM_PATH_ENV "HOME"
    #define PLATFORM_FOLDER ".gooseGame/boards/"
#elif __APPLE__
    #define PLATFORM_PATH_ENV "HOME"
    #define PLATFORM_FOLDER "Applications/gooseGame/boards/"
#endif


// GameTile* gameTiles = NULL;
Board board;

// get the position of a tile given its number
void getGameTilePosition(int tileNumber, int* x, int* y) {
  // convert tile number to zero-indexed array index
  tileNumber -= 1;

  // calculate x and y position of tile
  *x = board.gameTiles[tileNumber].x;
  *y = board.gameTiles[tileNumber].y;
}


int getGameTileType(int tileNumber) {
  // convert tile number to zero-indexed array index
  tileNumber -= 1;

  // return the type of the tile
  return board.gameTiles[tileNumber].type;
}

int getBoardMaxHeight() {
  int height = -1; // Initialize height with a value lower than any valid value

  for (int i = 0; i < board.numberOfTiles; i++) {
    if (board.gameTiles[i].y > height) {
      height = board.gameTiles[i].y;
    }
  }

  return height + 1;  // +1 because terrain always has an extra tile
}

int getBoardMaxWidth() {
  int width = -1; // Initialize width with a value lower than any valid value

  for (int i = 0; i < board.numberOfTiles; i++) {
    if (board.gameTiles[i].x > width) {
      width = board.gameTiles[i].x;
    }
  }

  return width + 1;
}


int getEndTilePosition(int *x, int *y){
  int endTile = board.numberOfTiles - 1;

  *x = board.gameTiles[endTile].x;
  *y = board.gameTiles[endTile].y;

  return endTile;
}

int getBoardLength(){
  return board.numberOfTiles;
}

void drawGameTile(int number) {
  int new_x = board.gameTiles[number].x * 6 + 1;
  int new_y = board.gameTiles[number].y * 3 + 1;

  setBackgroundColor(board.gameTiles[number].type, (board.gameTiles[number].type == END));
  moveCursor(new_x, new_y);
  if(board.gameTiles[number].type == END){
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

  for(int i = 0; i < board.numberOfTiles; i++){
    drawGameTile(i);
  }
}


void loadBoardFromFile(char *filePath) {
  clearConsole();
  char platformPath[FILE_PATH_LENGTH], fullPath[EXTRA_PATH_LENGTH];
  getPlatformFilePath(platformPath, PLATFORM_PATH_ENV, PLATFORM_FOLDER);


  sprintf(fullPath, "%s%s", platformPath, filePath);
  FILE* file = fopen(fullPath, "rb");
  if (file == NULL) {
    printf("Error opening file: %s\n", fullPath);
    return;
  }

  // Read the board data from the file
  fread(&board.numberOfTiles, sizeof(int), 1, file);
  fread(&board.name, sizeof(char), 20, file);

  // Dynamically allocate memory for the gameTiles array
  board.gameTiles = (GameTile *)malloc(sizeof(GameTile) * board.numberOfTiles);

  // Read the gameTiles data from the file
  for (int i = 0; i < board.numberOfTiles; i++) {
    GameTile tile;
    tile.x = 0; // Set an appropriate initial value
    tile.y = 0; // Set an appropriate initial value
    tile.type = 0; // Set an appropriate initial value
    fread(&tile, sizeof(GameTile), 1, file);
    board.gameTiles[i] = tile;
  }

  fclose(file);
}


void getBoardsInFolder(){
  clearConsole();
  char platformPath[FILE_PATH_LENGTH], fullPath[EXTRA_PATH_LENGTH];
  getPlatformFilePath(platformPath, PLATFORM_PATH_ENV, PLATFORM_FOLDER);

  // Open the directory
  DIR *dir = opendir(platformPath);
  if (dir == NULL) {
      printf("Error opening directory: %s\n", platformPath);
      return;
  }

  struct dirent *entry;
  int count = 0;

  // Allocate an array to store board names
  char** boardNames = (char**)malloc(sizeof(char*) * 100);  // Adjust the size as needed

  // Iterate over the entries in the directory
  while ((entry = readdir(dir)) != NULL) {
      // Filter out directories and hidden files
      if (entry->d_type == DT_REG && entry->d_name[0] != '.') {
          // Allocate memory for the board name
          boardNames[count] = (char*)malloc(strlen(entry->d_name) + 1);
          strcpy(boardNames[count], entry->d_name);

          printf("[%d] %s\n", count+1, boardNames[count]);
          count++;
      }
  }

  closedir(dir);

  printf("\n> ");
  int selection;
  getNumberFromRange(&selection, 1, count);

  loadBoardFromFile(boardNames[selection-1]);

  // Free the allocated memory for board names
  for (int i = 0; i < count; i++) {
      free(boardNames[i]);
  }
  free(boardNames);
}

void freeBoard(){
  free(board.gameTiles);
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

void installBoards(){
  char platformPath[FILE_PATH_LENGTH], fullPath[EXTRA_PATH_LENGTH];
  getPlatformFilePath(platformPath, PLATFORM_PATH_ENV, PLATFORM_FOLDER);

  FILE *file;


  GameTile smallTiles[] = {
      {1, 1, TRUEFALSE},
      {2, 1, MULTIPLE},
      {3, 1, WRITTEN},
      {4, 1, TRUEFALSE},
      {5, 1, MULTIPLE},
      {6, 1, WRITTEN},
      {6, 2, TRUEFALSE},
      {6, 3, MULTIPLE},
      {6, 4, WRITTEN},
      {6, 5, END}
  };

  Board small = {
    10,
    "small.dat",
    smallTiles
  };

  snprintf(fullPath, EXTRA_PATH_LENGTH, "%s%s", platformPath, small.name);
  file = fopen(fullPath, "rb");
  if(file == NULL){
    file = fopen(fullPath, "wb");
    if(file == NULL){
      printf("Error opening file for writing: %s\n", fullPath);
      waitInput("...");
      return;
    }

    // Write the board data to the file
    fwrite(&small.numberOfTiles, sizeof(int), 1, file);
    fwrite(&small.name, sizeof(char), 20, file);

    // Write the gameTiles data to the file
    fwrite(small.gameTiles, sizeof(GameTile), small.numberOfTiles, file);
  }
  fclose(file);

  GameTile mediumTiles[] = {
      {1, 1, TRUEFALSE},
      {2, 1, END},
      {3, 1, WRITTEN},
      {4, 1, TRUEFALSE},
      {5, 1, MULTIPLE},
      {6, 1, WRITTEN},
      {6, 2, TRUEFALSE},
      {6, 3, MULTIPLE},
      {6, 4, WRITTEN},
      {6, 5, TRUEFALSE},
      {6, 6, TRUEFALSE},
      {6, 7, WRITTEN},
      {6, 8, TRUEFALSE},
      {6, 9, MULTIPLE},
      {5, 9, TRUEFALSE},
      {4, 9, WRITTEN},
      {3, 9, MULTIPLE},
      {3, 8, WRITTEN},
      {3, 7, TRUEFALSE},
      {3, 6, END},
  };


  Board medium = {
    20,
    "medium.dat",
    mediumTiles
  };

  snprintf(fullPath, EXTRA_PATH_LENGTH, "%s%s", platformPath, medium.name);
  file = fopen(fullPath, "rb");
  if(file == NULL){
    file = fopen(fullPath, "wb");
    if(file == NULL){
      return;
    }

    // Write the board data to the file
    fwrite(&medium.numberOfTiles, sizeof(int), 1, file);
    fwrite(&medium.name, sizeof(char), 20, file);

    // Write the gameTiles data to the file
    fwrite(medium.gameTiles, sizeof(GameTile), medium.numberOfTiles, file);
  }

  fclose(file);
}
