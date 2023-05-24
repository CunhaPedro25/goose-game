#include "game.h"

int initializeGame(){
  int numPlayers;

  printf("How many players are in the game? (Max: 4)\n");
  printf("> ");
  getNumberFromRange(&numPlayers, 1, 4);

  storeRandomizeBoolQuestions();

  clearConsole();
  drawBoard();

  for(int id = 1; id <= numPlayers; id++){
    drawPlayer(id,1);
  }
}

void gameLoop(){
  bool gameover = false;
  int numberOfSpaces = 0;
  int optionAnswer = 0;
  char writtenAnswer[100];
  int cursorYposition = (getBoardMaxHeight()+3) * 3 + 1;  //Covert to screen position (screen_y = y * 3 + 1)
  int numPlayers = initializeGame();

  do{
    for(int id = 1; id <= numPlayers; id++){
      moveCursor(0,cursorYposition);
      clearToScreenEnd();
      bool correct;
      numberOfSpaces = (rand() % getBoardLength()-1)+1;
      // numberOfSpaces = 23;
      printf("%s's turn | Points: %2d | Question Points: +%d\n", getPlayerName(id), playerCurrentTile(id)-1, numberOfSpaces);

      BoolQuestion* question = getBoolQuestion();
      switch(getGameTileType(playerCurrentTile(id))){
        case BOOL:
          //BoolQuestion* question = getBoolQuestion();

          printf("%s\n", question->question);
          printf("1 - True\n2 - False\n");

          getNumberFromRange(&optionAnswer, 1,2);
          correct = optionAnswer == question->answer && question->answer == 1 ? true : optionAnswer != question->answer && optionAnswer != 1 && question->answer == 0 ? true : false;
          break;
        case MULTIPLE:
          //MultipleChoiceQuestion* question = getMultipleChoiceQuestion();

            printf("%s\n", question->question);
              printf("1 - True\n2 - False\n");

              getNumberFromRange(&optionAnswer, 1,2);
              correct = optionAnswer == question->answer && question->answer == 1 ? true : optionAnswer != question->answer && optionAnswer != 1 && question->answer == 0 ? true : false;
              break;
        case WRITTEN:
          //MultipleChoiceQuestion* question = getMultipleChoiceQuestion();

            printf("%s\n", question->question);
              printf("1 - True\n2 - False\n");

              getNumberFromRange(&optionAnswer, 1,2);
              correct = optionAnswer == question->answer && question->answer == 1 ? true : optionAnswer != question->answer && optionAnswer != 1 && question->answer == 0 ? true : false;
              break;
      }

      if(correct){
        printf("Correct!\n");
        saveCursor();
        if(playerCurrentTile(id) + numberOfSpaces < getBoardLength()){
          drawPlayer(id, playerCurrentTile(id) + numberOfSpaces);
        }else{
          drawPlayer(id, getBoardLength());
          gameover = true;
          printf("%s WON!\n", getPlayerName(id));
          printf("%d points", playerCurrentTile(id)-1);
          break;
        }
      }else{
        printf("Wrong!\n");
        saveCursor();
        if(playerCurrentTile(id) - numberOfSpaces > 0){
          drawPlayer(id, playerCurrentTile(id) - numberOfSpaces);
        }else{
          drawPlayer(id, 1);
        }
      }

        restoreCursor();
        printf("Press any key to continue...");
        getchar();
    }

  }while(!gameover);

  moveCursor(0,cursorYposition);
  clearToScreenEnd();
  printf("Press any key to continue...");
  getchar();

  freeBoolQuestionList();
}
