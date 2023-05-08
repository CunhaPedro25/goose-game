#include "terrain.h"
#include "../utils/ui.h"

void addSandToWater(int **map, int size){
  int i, j;

  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      if (map[i][j] == WATER) {
        if (i > 0 && map[i-1][j] != WATER) {
          map[i-1][j] = SAND;
        }
        if (i < size-1 && map[i+1][j] != WATER) {
          map[i+1][j] = SAND;
        }
        if (j > 0 && map[i][j-1] != WATER) {
          map[i][j-1] = SAND;
        }
        if (j < size-1 && map[i][j+1] != WATER) {
          map[i][j+1] = SAND;
        }
      }
    }
  }

}

void generateWater(int **map, int size){
  int num_water_tiles = 0;
  int max_water_tiles = size * size / 6;
  
  int i = 0;
  int j = 0;

  // add some random water tiles
  for (int k = 0; k < 3; k++) {
      i = rand() % size;
      j = rand() % size;
      map[i][j] = WATER;
      num_water_tiles++;
  }

  while (num_water_tiles < max_water_tiles) {
    for (i = 0; i < size; i++) {
      for (j = 0; j < size; j++) {
        if (map[i][j] == WATER) {
          if (i > 0 && map[i-1][j] != WATER && rand() % 2 == 0) {
            map[i-1][j] = WATER;
            num_water_tiles++;
          }
          if (i < size-1 && map[i+1][j] != WATER && rand() % 2 == 0) {
            map[i+1][j] = WATER;
            num_water_tiles++;
          }
          if (j > 0 && map[i][j-1] != WATER && rand() % 2 == 0) {
            map[i][j-1] = WATER;
            num_water_tiles++;
          }
          if (j < size-1 && map[i][j+1] != WATER && rand() % 2 == 0) {
            map[i][j+1] = WATER;
            num_water_tiles++;
          }
        }
      }
    }
  }

  addSandToWater(map, size);
}

void generateTerrain(int **map, int size){
  int i, j;

  // seed the random number generator
  srand(time(NULL));

  // initialize map to either dirt
  for (i = 0; i < size; i++) {
      for (j = 0; j < size; j++) {
        map[i][j] = DIRT;
      }
  }

  generateWater(map, size);


  
}

void drawTerrain(int size){
  int **map;

  map = (int **) malloc(size * sizeof(int*));
  for(int i = 0; i < size; i++){
    map[i] = (int *) malloc(size * sizeof(int));
  }

  generateTerrain(map, size);

  int new_x = 0;
  int new_y = 0;

  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      new_x = j * 6 +1; 
      new_y = i * 3 +1;

      moveCursor(new_x, new_y);
      printf("\e[%dm      \e[0m", 100+map[i][j]);
      moveCursor(new_x, new_y+1);
      printf("\e[%dm      \e[0m", 100+map[i][j]);
      moveCursor(new_x, new_y+2);
      printf("\e[%dm      \e[0m", 100+map[i][j]);
    }
  }


  free(map);
}