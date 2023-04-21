// in player.c
#include "player.h"
#include "../utils/ui.h"
#include "../tiles/tiles.h"

Player players[4] = {
    { RED, 0 },
    { GREEN, 0 },
};

void drawPlayer(int id, int tile) {
    int oldTile = players[id - 1].currentTile;
    int x, y;

    // get position of old tile
    getTilePosition(oldTile + 1, &x, &y);

    // calculate coordinates of old player position
    int old_player_x = y * 5 + players[id - 1].id + 1;
    int old_player_y = x * 2 + 1 + 1;

    // clear old player position
    moveCursor(old_player_x, old_player_y);
    printf(" ");

    // update player's current tile
    players[id - 1].currentTile = tile - 1;

    // get position of new tile
    getTilePosition(tile, &x, &y);

    // calculate coordinates of new player position
    int new_player_x = y * 5 + players[id - 1].id + 1;
    int new_player_y = x * 2 + 1 + 1;

    // draw player on new tile
    moveCursor(new_player_x, new_player_y);
    printf("\e[%dm", 30 + id);
    printf("o");
    printf("\e[%dm", 0);
}
