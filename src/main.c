#include <stdio.h>
#include "board/board.h"
#include "player/player.h"
#include "utils/ui.h"
#include "utils/functions.h"

int main(){
  clearConsole();

  drawBoard();

  for (int i = 1; i <= 4; i++){
    drawPlayer(i, 1);
  }

  int selection;

  int cursorYposition = (getBoardMaxHeight()+3) * 3 + 1;  //Covert to screen position (screen_y = y * 3 + 1)
  do{
    moveCursor(0,cursorYposition);
    printf("Select Tile >");
    drawPlayer(RED, selection = getNumber());
  }while(selection != 0);

  clearConsole();

  return 0;
}
