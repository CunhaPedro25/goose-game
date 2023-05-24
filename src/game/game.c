#include "game.h"

int initializeGame(){
  int numPlayers;

  printf("How many players are in the game? (Max: 4)\n");
  printf("> ");
  getNumberFromRange(&numPlayers, 1, 4);

  storeRandomizeBoolQuestions();

  clearConsole();
  drawBoard();

  for(int id = 0; id < numPlayers; id++){
    drawPlayer(id,1);
  }
}

void firstRound(int *order, int numPlayers){
    int *dice = (int *) malloc(numPlayers * sizeof(int));
    if (dice == NULL) {
        // Error handling for memory allocation failure
        printf("Error: Memory allocation failed for dice array.\n");
        return;
    }

    int cursorYposition = (getBoardMaxHeight()+3) * 3 + 1;  //Covert to screen position (screen_y = y * 3 + 1)

    moveCursor(0, cursorYposition);

    printf("Each player will roll a dice to define the order of the game.\n");
    waitInput("Press any key to roll the dices...");

    moveCursor(0, cursorYposition);
    clearToScreenEnd();
    setTextColor(YELLOW, 0);
    printf("DICE RESULTS!\n");
    resetColor();
    for(int id = 0; id < numPlayers; id++){
        dice[id] = (rand() % 5)+1;
        order[id] = id;
        printf("%s's dice: %d\n", getPlayerName(id), dice[id]);
    }

    // Handle equal dice rolls
    int temp;
    int equalRollCount = 0;
    int *equalRollPlayers = (int *) malloc(numPlayers * sizeof(int));
    if (equalRollPlayers == NULL) {
        // Error handling for memory allocation failure
        printf("Error: Memory allocation failed for equalRollPlayers array.\n");
        free(dice);
        return;
    }

    do {
      equalRollCount = 0;

      for (int i = 0; i < numPlayers - 1; i++) {
        if (dice[i] == dice[i + 1]) {
          equalRollPlayers[equalRollCount] = order[i];
          equalRollPlayers[equalRollCount + 1] = order[i + 1];
          equalRollCount++;
        }
      }

      if (equalRollCount > 0) {
        setTextColor(RED, 0);
        printf("\nEqual dice rolls!");
        resetColor();

        waitInput("\nPress any key to rematch...");

        moveCursor(0, cursorYposition);
        clearToScreenEnd();
        setTextColor(YELLOW, 0);
        printf("DICE RESULTS!\n");
        resetColor();
        for (int i = 0; i < equalRollCount + 1; i++) {
          dice[equalRollPlayers[i]] = (rand() % 5) + 1;
          printf("%s's dice roll: %d\n", getPlayerName(equalRollPlayers[i]), dice[equalRollPlayers[i]]);
        }

        // Sort the players with equal rolls based on their additional dice rolls
        for (int i = 0; i < equalRollCount; i++) {
          for (int j = 0; j < equalRollCount - i; j++) {
            if (dice[equalRollPlayers[j]] < dice[equalRollPlayers[j + 1]]) {
              temp = equalRollPlayers[j];
              equalRollPlayers[j] = equalRollPlayers[j + 1];
              equalRollPlayers[j + 1] = temp;
            }
          }
        }
      }
    } while (equalRollCount > 0);

    // Sort the players based on their dice rolls
    for (int i = 0; i < numPlayers - 1; i++) {
        for (int j = 0; j < numPlayers - i - 1; j++) {
            if (dice[j] < dice[j + 1]) {
                // Swap the players' indices
                temp = order[j];
                order[j] = order[j + 1];
                order[j + 1] = temp;

                // Swap the dice rolls
                temp = dice[j];
                dice[j] = dice[j + 1];
                dice[j + 1] = temp;
            }
        }
    }

    printf("\nThe order will be:\n");
    for(int i = 0; i < numPlayers; i++){
      printf("Player %d: %s\n", i+1, getPlayerName(order[i]));
    }

    waitInput("\nPress any key to continue...");

    free(equalRollPlayers);
    free(dice);
}

void gameLoop(){
  bool gameover = false;
  int numberOfSpaces = 0;
  int optionAnswer = 0;
  char writtenAnswer[100];
  int cursorYposition = (getBoardMaxHeight()+3) * 3 + 1;  //Covert to screen position (screen_y = y * 3 + 1)
  int numPlayers = initializeGame();
  int *order = NULL;

  order = (int *) malloc(numPlayers * sizeof(int));

  firstRound(order, numPlayers);

  do{
    for(int id = 0; id < numPlayers; id++){
      moveCursor(0,cursorYposition);
      clearToScreenEnd();
      bool correct;
      numberOfSpaces = (rand() % 5)+1;
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
        waitInput("Press any key to continue...");
    }

  }while(!gameover);

  moveCursor(0,cursorYposition);
  waitInput("Press any key to continue...");

  freeBoolQuestionList();
}
