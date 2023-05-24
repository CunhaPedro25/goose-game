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

  // addNewBoolQuestion("False?", false);
  // addNewBoolQuestion("True?", true);
  // addNewBoolQuestion("False?", false);
  // addNewBoolQuestion("False?", false);
  // addNewBoolQuestion("True?", true);

  // storeRandomizeBoolQuestions();
  // int numQuestions = getNumberBoolQuestions();

  // // Print the linked list
  // printf("Questions:\n");
  // for(int i = 0; i < numQuestions; i++){
  //     BoolQuestion* question = getQuestion();
  //     int answer;
  //     printf("%s\n", question->question);

  //     scanf("%d", &answer);
  //     if(answer == question->answer){
  //       printf("Correct!\n");
  //     }else{
  //       printf("Wrong!\n");
  //     }

  //     free(question);
  // }

  // getchar();
  // getchar();
  // getchar();

  // return 0;

  // int selection;

  // int cursorYposition = (getBoardMaxHeight()+3) * 3 + 1;  //Covert to screen position (screen_y = y * 3 + 1)
  // do{
  //   moveCursor(0,cursorYposition);
  //   printf("Select Tile >");
  //   drawPlayer(RED, selection = getNumber());
  // }while(selection != 0);

  gameLoop();

  clearConsole();

  return 0;
}
