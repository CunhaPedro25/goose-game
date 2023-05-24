// in player.c
#include "player.h"

Player players[4] = {
    { RED, "Ronaldo", 0},
    { GREEN, "Pepe", 0 },
    { YELLOW, "Messi", 0},
    { BLUE, "Mono", 0 },
};

char *getPlayerName(int id){
    return players[id-1].name;
}

int playerCurrentTile(int id){
    return players[id - 1].currentTile;
}

void drawPlayer(int id, int tile) {
    int x, y;
    int oldTile = playerCurrentTile(id);

    if(oldTile != 0){
        // get position of old tile
        getGameTilePosition(oldTile, &x, &y);

        // calculate coordinates of old player position
        int old_player_x = x * 6 + players[id - 1].id + 1;
        int old_player_y = y * 3 + 1 + 1;

        // clear old player position
        moveCursor(old_player_x, old_player_y);
        setBackgroundColor(getGameTileType(oldTile), 0);
        printf(" ");
        resetColor();
    }

    // update player's current tile
    players[id - 1].currentTile = tile;

    // get position of new tile
    getGameTilePosition(tile, &x, &y);

    // calculate coordinates of new player position
    int new_player_x = x * 6 + id + 1;
    int new_player_y = y * 3 + 1 + 1;

    // draw player on new tile
    moveCursor(new_player_x, new_player_y);
    setBackgroundColor(id, 1);
    setTextColor(id, 0);
    printf("o");
    resetColor();
}
