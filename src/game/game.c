#include "game.h"

void initializeGame(int numPlayers){
  storeRandomizeBoolQuestions();

  drawBoard();

  for(int id = 1; id <= numPlayers; id++){
    drawPlayer(id,1);
  }
}

void gameLoop(int numPlayers){
  int gameover = false;
  int numberOfSpaces = 0;
  int cursorYposition = (getBoardMaxHeight()+3) * 3 + 1;  //Covert to screen position (screen_y = y * 3 + 1)
  initializeGame(numPlayers);

  do{
    for(int id = 1; id <= numPlayers; id++){
      BoolQuestion* question = getQuestion();
      numberOfSpaces = 2;

      int answer;
      moveCursor(0,cursorYposition);
      clearToScreenEnd();
      printf("Questions for Player %d\n", id);
      printf("%s\n", question->question);

      printf("Resposta: ");
      scanf("%d", &answer);
      if(answer == question->answer){
        printf("Correct!\n");
        if(playerCurrentTile(id) + numberOfSpaces < getBoardLength()){
          drawPlayer(id, playerCurrentTile(id) + numberOfSpaces);
        }else{
          drawPlayer(id, getBoardLength());
        }
      }else{
        printf("Wrong!\n");
        if(playerCurrentTile(id) - numberOfSpaces > 0){
          drawPlayer(id, playerCurrentTile(id) - numberOfSpaces);
        }else{
          drawPlayer(id, 1);
        }
      }
    }

  }while(!gameover);

  freeBoolQuestionList();
}
