#include <stdio.h>
#include "board/board.h"
#include "player/player.h"
#include "utils/ui.h"
#include "utils/functions.h"

int main(){
  clearConsole();

  drawBoard();

  for (int i = 1; i < 2; i++){
    drawPlayer(i, 1);
  }

  int selection;
  do{
    moveCursor(0,10);
    printf("Select Tile >");
    drawPlayer(RED, selection = getNumber());
  }while(selection != 0);

  clearConsole();

  return 0;
}
