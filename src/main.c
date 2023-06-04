#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "board/board.h"
#include "game/game.h"
#include "player/player.h"
#include "questions/questions.h"
#include "utils/ui.h"
#include "utils/functions.h"
#include "utils/menus.h"

void settings(){
  printf("%d", getNumberMultipleChoiceQuestions());

  waitInput("...");
}

int main(){
  clearConsole();

  int selection;

  installGame();

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
