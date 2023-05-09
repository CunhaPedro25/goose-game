#include "terrain.h"
#include "board.h"
#include "../utils/ui.h"

void addSandToWater(int **map, int width, int height){
  int i, j;

  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      if (map[i][j] == WATER) {
        if (i > 0 && map[i-1][j] != WATER) {
          map[i-1][j] = SAND;
        }
        if (i < height-1 && map[i+1][j] != WATER) {
          map[i+1][j] = SAND;
        }
        if (j > 0 && map[i][j-1] != WATER) {
          map[i][j-1] = SAND;
        }
        if (j < width-1 && map[i][j+1] != WATER) {
          map[i][j+1] = SAND;
        }
      }
    }
  }

}

void generateWater(int **map, int width, int height){
  int num_water_tiles = 0;
  int max_water_tiles = width * height / 8;
  
  int i = 0;
  int j = 0;

  // add some random water tiles
  getEndTilePosition(&i, &j);
  map[j][i] = WATER;
  if(j > 0){   
    map[j-1][i] = WATER;
  }
  map[j+1][i] = WATER;
  if(i > 0){
    map[j][i-1] = WATER;
  }
  map[j][i+1] = WATER;
  num_water_tiles += 5;

  for (int k = 0; k < 2; k++) {
      i = rand() % height;
      j = rand() % width;
      map[i][j] = WATER;
      num_water_tiles++;
  }

  while (num_water_tiles < max_water_tiles) {
    for (i = 0; i < height; i++) {
      for (j = 0; j < width; j++) {
        if (map[i][j] == WATER) {
          if (i > 0 && map[i-1][j] != WATER && rand() % 2 == 0) {
            map[i-1][j] = WATER;
            num_water_tiles++;
          }
          if (i < height-1 && map[i+1][j] != WATER && rand() % 2 == 0) {
            map[i+1][j] = WATER;
            num_water_tiles++;
          }
          if (j > 0 && map[i][j-1] != WATER && rand() % 2 == 0) {
            map[i][j-1] = WATER;
            num_water_tiles++;
          }
          if (j < width-1 && map[i][j+1] != WATER && rand() % 2 == 0) {
            map[i][j+1] = WATER;
            num_water_tiles++;
          }
        }
      }
    }
  }

  addSandToWater(map, width, height);
}

void generateTerrain(int **map, int width, int height){
  int i, j;

  // seed the random number generator
  srand(time(NULL));

  // initialize map to either dirt
  for (i = 0; i < height; i++) {
      for (j = 0; j < width; j++) {
        map[i][j] = DIRT;
      }
  }

  generateWater(map, width, height);
}

void drawTerrain(){
  int **map;
  int height = getBoardMaxHeight()+2;
  int width = getBoardMaxWidth()+2;

  map = (int **) malloc(height * sizeof(int*));
  for(int i = 0; i < height; i++){
    map[i] = (int *) malloc(width * sizeof(int));
  }

  generateTerrain(map, width, height);

  int x = 0;
  int y = 0;

  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      x = j * 6 +1; 
      y = i * 3 +1;

      setBackgroundColor(map[i][j], 1);
      for (int i = 0; i < 3; i++)
      {
        moveCursor(x, y + i);
        printf("      ");
      }
      resetColor();
    }
  }


  free(map);
}