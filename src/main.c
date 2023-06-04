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

int main(){
  clearConsole();

  installGame();
  gameLoop();

  clearConsole();

  return 0;
}
