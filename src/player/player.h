#ifndef PLAYER_H
#define PLAYER_H

typedef struct player {
  int id;
  int currentTile;
} Player;

void drawPlayer(int id, int tile);

#endif