#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "board/board.h"
#include "game/game.h"
#include "player/player.h"
#include "questions/questions.h"
#include "utils/ui/ui.h"
#include "utils/functions/functions.h"
#include "utils/menus/menus.h"

// #define FILE_PATH_LENGTH 256
// #define EXTRA_PATH_LENGTH 512

// #ifdef _WIN32
//     #define PLATFORM_PATH_ENV "LOCALAPPDATA"
//     #define PLATFORM_FOLDER "gooseGame\\boards\\"
// #elif __linux__
//     #define PLATFORM_PATH_ENV "HOME"
//     #define PLATFORM_FOLDER ".gooseGame/boards/"
// #elif __APPLE__
//     #define PLATFORM_PATH_ENV "HOME"
//     #define PLATFORM_FOLDER "Applications/gooseGame/boards/"
// #endif

// Board globalBoard;


// void showBoard() {
//   printf("Board Name: %s\n", globalBoard.name);
//   printf("Number of Tiles: %d\n", globalBoard.numberOfTiles);

//   printf("Tiles:\n");
//   for (int i = 0; i < globalBoard.numberOfTiles; i++) {
//       GameTile tile = globalBoard.gameTiles[i];
//       printf("Tile %d: (%d, %d) - Type: %d\n", i + 1, tile.x, tile.y, tile.type);
//   }
// }


// void loadBoardFromFile() {
//   clearConsole();
//   char platformPath[FILE_PATH_LENGTH], fullPath[EXTRA_PATH_LENGTH];
//   getPlatformFilePath(platformPath, PLATFORM_PATH_ENV, PLATFORM_FOLDER);


//   sprintf(fullPath, "%s%s", platformPath, "small.dat");
//   FILE* file = fopen(fullPath, "rb");
//   if (file == NULL) {
//     printf("Error opening file: %s\n", fullPath);
//     return;
//   }

//   // Read the board data from the file
//   fread(&globalBoard.numberOfTiles, sizeof(int), 1, file);
//   fread(&globalBoard.name, sizeof(char), 20, file);

//   // Dynamically allocate memory for the gameTiles array
//   globalBoard.gameTiles = (GameTile *)malloc(sizeof(GameTile) * globalBoard.numberOfTiles);

//   // Read the gameTiles data from the file
//   for (int i = 0; i < globalBoard.numberOfTiles; i++) {
//     GameTile tile;
//     tile.x = 0; // Set an appropriate initial value
//     tile.y = 0; // Set an appropriate initial value
//     tile.type = 0; // Set an appropriate initial value
//     fread(&tile, sizeof(GameTile), 1, file);
//     globalBoard.gameTiles[i] = tile;
//   }

//   fclose(file);
// }


int main(){
  clearConsole();

  int selection;

  installGame();

  // loadBoardFromFile();
  // showBoard();

  // free(globalBoard.gameTiles);

  do{
    MenuOptions options[] = {
      {"Play", gameLoop},
      {"Settings", settings}
    };

    selection = menu("Goose Game", options, sizeof(options)/sizeof(options[0]), "main");

    if(selection != 0) options[selection-1].callback();
  }while(selection != 0);

  clearConsole();
  return 0;
}
