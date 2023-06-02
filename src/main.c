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

  // printf("%s", getBoolQuestion(2)->question);

  Questions question = { "test", "test"};

  // addNewMultipleChoiceQuestion(question);

  // int numQuestions = getNumberMultipleChoiceQuestions();

  // printf("%d\n", numQuestions);

  // for(int i = 1; i <= numQuestions; i++){
  //   Questions* getQuestion = getMultipleChoiceQuestion(i);
  //   printf("%s\n", getQuestion->question);
  //   printf("%s\n", getQuestion->answer);

  //   for(int j = 0; j < 3; j++){
  //     printf("%s\n", getQuestion->wrongAnswers[j]);
  //   }
  //   printf("\n");
  // }

  for(int i = 0; i < 5; i++){
    addNewBoolQuestion(question);
  }

  int numQuestions = getNumberBoolQuestions();

  for(int i = 1; i <= numQuestions; i++){
    Questions* getQuestion = getBoolQuestion(i);
    printf("%s\n", getQuestion->question);
    printf("%s\n\n", getQuestion->answer);
  }

  Questions newQuestion = { "not cool", "pog"};
  editBoolQuestion(2, newQuestion);

  printf("Edit\n");
  for(int i = 1; i <= numQuestions; i++){
    Questions* getQuestion = getBoolQuestion(i);
    printf("%s\n", getQuestion->question);
    printf("%s\n\n", getQuestion->answer);
  }

  deleteBoolQuestion(2);

  numQuestions = getNumberBoolQuestions();

  printf("Delete\n");
  for(int i = 1; i <= numQuestions; i++){
    Questions* getQuestion = getBoolQuestion(i);
    printf("%s\n", getQuestion->question);
    printf("%s\n\n", getQuestion->answer);
  }

  QuestionNode* boolQuestionList = NULL;

  storeRandomizedBoolQuestions(boolQuestionList);

  Questions* getQuestion = getQuestionFromList(boolQuestionList);
  printf("%s\n", getQuestion->question);
  printf("%s\n\n", getQuestion->answer);

  freeQuestionList(boolQuestionList);


  // addNewWrittenQuestion(question);
  // Questions* getQuestion  = getWrittenQuestion(1);
  // printf("%s\n", getQuestion->question);
  // printf("%s\n", getQuestion->answer);

  getchar();

  // int selection;

  // int cursorYposition = (getBoardMaxHeight()+3) * 3 + 1;  //Covert to screen position (screen_y = y * 3 + 1)
  // do{
  //   moveCursor(0,cursorYposition);
  //   printf("Select Tile >");
  //   drawPlayer(RED, selection = getNumber());
  // }while(selection != 0);

  // gameLoop();

  clearConsole();

  return 0;
}
