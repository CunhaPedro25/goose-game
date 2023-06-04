#ifndef TERRAIN_H
#define TERRAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"
#include "../utils/ui.h"

enum terrain{
  NOTHING,
  LAVA,
  DIRT,
  SAND,
  WATER
};

void drawTerrain();

#endif
