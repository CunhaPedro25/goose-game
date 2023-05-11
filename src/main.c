#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "board/board.h"
#include "player/player.h"
#include "questions/questions.h"
#include "utils/ui.h"
#include "utils/functions.h"

int main(){
  clearConsole();

  addNewBoolQuestion("Question 1", false);
  addNewBoolQuestion("Question 2", true);
  addNewBoolQuestion("Question 3", false);
  addNewBoolQuestion("Question 4", false);
  addNewBoolQuestion("Question 5", true);

  storeRandomizeBoolQuestions();
  int numQuestions = getNumberBoolQuestions();

  // Print the linked list
  printf("Questions:\n");
  for(int i = 0; i < numQuestions; i++){
      BoolQuestion* question = getQuestion();
      printf("%s %d\n", question->question, question->answer);
      free(question);
  }

  getchar();
  clearConsole();

  return 0;


  // int selection;

  // int cursorYposition = (getBoardMaxHeight()+3) * 3 + 1;  //Covert to screen position (screen_y = y * 3 + 1)
  // do{
  //   moveCursor(0,cursorYposition);
  //   printf("Select Tile >");
  //   drawPlayer(RED, selection = getNumber());
  // }while(selection != 0);

  // clearConsole();

  // return 0;
}
