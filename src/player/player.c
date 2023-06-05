// in player.c
#include "player.h"

Player *players = NULL;

void createPlayers(int numPlayers){
    players = (Player*) malloc(numPlayers * sizeof(Player));
    for(int i = 0; i < numPlayers; i++){
        players[i].currentTile = 0;
    }
}

void freePlayers(){
    free(players);
}

bool isNameTaken(const char* name, int currentPlayer) {
  for (int i = 0; i < currentPlayer; i++) {
    if (strcasecmp(players[i].name, name) == 0) {
        showSpecificInvalidOption("[Name Already Taken]");
        restoreCursor();
        clearToLineEnd();
        return true;
    }
  }
  return false;
}

void savePlayerName(int id, char *newName){
    strncpy(players[id].name, newName, sizeof(players[id].name) - 1);
    players[id].name[sizeof(players[id].name) - 1] = '\0';
}

bool isColorTaken(int color, int currentPlayer) {
  for (int i = 0; i < currentPlayer; i++) {
    if (players[i].color == color) {
      return true;
    }
  }
  return false;
}

void savePlayerColor(int id, int color){
    players[id].color = color;
}

char *getPlayerName(int id){
    return players[id].name;
}

int playerCurrentTile(int id){
    return players[id].currentTile;
}

void getPlayer(Player* player, int id){
  *player =  players[id];
}

void drawPlayer(int id, int tile) {
    int x, y;
    int oldTile = playerCurrentTile(id);

    if(oldTile != 0){
        // get position of old tile
        getGameTilePosition(oldTile, &x, &y);

        // calculate coordinates of old player position
        int old_player_x = x * 6 + (id+1) + 1;
        int old_player_y = y * 3 + 1 + 1;

        // clear old player position
        moveCursor(old_player_x, old_player_y);
        setBackgroundColor(getGameTileType(oldTile), 0);
        printf(" ");
        resetColor();
    }

    // update player's current tile
    players[id].currentTile = tile;

    // get position of new tile
    getGameTilePosition(tile, &x, &y);

    // calculate coordinates of new player position
    int new_player_x = x * 6 + (id+1) + 1;
    int new_player_y = y * 3 + 1 + 1;

    // draw player on new tile
    moveCursor(new_player_x, new_player_y);
    setBackgroundColor(players[id].color, 1);
    setTextColor(players[id].color, 0);
    printf("o");
    resetColor();
}
