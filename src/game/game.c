#include "game.h"

int initializeGame(QuestionNode* boolQuestionList, QuestionNode* multipleChoiceQuestionList){
  int numPlayers;

  printf("How many players are in the game? (Min: 2; Max: 4)\n");
  printf("> ");
  getNumberFromRange(&numPlayers, 2, 4);

  storeRandomizeQuestions(boolQuestionList);
  storeRandomizeQuestions(multipleChoiceQuestionList);

  clearConsole();
  drawBoard();

  for(int id = 0; id < numPlayers; id++){
    drawPlayer(id,1);
  }
}

void determinePlayerOrder(int *order, int numPlayers){
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
        dice[id] = rand() % 6 +1;
        order[id] = id;
        printf("%s's dice: %d\n", getPlayerName(id), dice[id]);
    }

    // // Handle equal dice rolls
    // int equalRollCount = 0;
    // // Allocate the flag array to keep track of players already added
    // int *playerAdded = (int *) calloc(numPlayers, sizeof(int));
    // if (playerAdded == NULL) {
    //     // Error handling for memory allocation failure
    //     printf("Error: Memory allocation failed for playerAdded array.\n");
    //     free(dice);
    //     return;
    // }

    // do {
    //   equalRollCount = 0;

    //   for (int i = 0; i < numPlayers; i++) {
    //     if(!playerAdded[i]){
    //       for (int j = i + 1; j < numPlayers; j++) {
    //         if (dice[i] == dice[j] && !playerAdded[j]) {
    //           playerAdded[i] = 1;
    //           playerAdded[j] = 1;
    //           equalRollCount++;
    //         }
    //       }
    //       if(equalRollCount == 0){
    //         playerAdded[i] = 0;
    //       }
    //     }
    //   }

    //   if (equalRollCount > 0) {
    //     setTextColor(RED, 0);
    //     printf("\nEqual dice rolls!");
    //     resetColor();

    //     waitInput("\nPress any key to rematch...");

    //     moveCursor(0, cursorYposition);
    //     clearToScreenEnd();
    //     setTextColor(YELLOW, 0);
    //     printf("DICE RESULTS!\n");
    //     resetColor();
    //     for (int i = 0; i < numPlayers; i++) {
    //       if(playerAdded[i]){
    //         dice[i] = rand() % 6 + 1;
    //         printf("%s's dice roll: %d\n", getPlayerName(i), dice[i]);
    //       }
    //     }
    //   }
    // } while (equalRollCount > 0);

    // free(playerAdded);

    // Sort the players based on their dice rolls
    int temp;
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

    free(dice);
}

void gameLoop(){
  QuestionNode* boolQuestionList = NULL;
  QuestionNode* multipleChoiceQuestionList = NULL;

  bool gameover = false;
  int numberOfSpaces = 0;
  int optionAnswer = 0;
  char writtenAnswer[100];
  int cursorYposition = (getBoardMaxHeight()+3) * 3 + 1;  //Covert to screen position (screen_y = y * 3 + 1)
  Questions* question = NULL;

  // Call function to ask for numPlayers, create map, and draw players
  int numPlayers = initializeGame(boolQuestionList, multipleChoiceQuestionList);

  int *order = (int *) malloc(numPlayers * sizeof(int));
  if (order == NULL) {
      // Error handling for memory allocation failure
      printf("Error: Memory allocation failed for order array.\n");
      return;
  }

  determinePlayerOrder(order, numPlayers);

  do{
    for(int id = 0; id < numPlayers; id++){
      moveCursor(0,cursorYposition);
      clearToScreenEnd();

      bool correct;
      numberOfSpaces = rand() % 6 + 1;

      printf("%s's turn | Points: %2d \n", getPlayerName(order[id]), playerCurrentTile(order[id])-1);
      printf("Question Type: %d | Question Points: +%d\n", getGameTileType(playerCurrentTile(id)), numberOfSpaces);

      switch(getGameTileType(playerCurrentTile(id))){
        case BOOL:
            question = getRandomBoolQuestion(boolQuestionList);

            printf("%s\n", question->question);
            printf("1 - True\n2 - False\n");

            getNumberFromRange(&optionAnswer, 1,2);
            correct = verifyBoolQuestion(question->answer, optionAnswer);
          break;
        case MULTIPLE:
            question = getRandomMultipleChoiceQuestion(multipleChoiceQuestionList);

            int correctIndex = getCorrectAnswerIndex(question->answer, question->wrongAnswers);
            getNumberFromRange(&optionAnswer, 1,2);

            correct = (optionAnswer == correctIndex);
          break;
        case WRITTEN:
            question = getRandomBoolQuestion(boolQuestionList);

            printf("%s\n", question->question);
            printf("1 - True\n2 - False\n");

            getNumberFromRange(&optionAnswer, 1,2);
            correct = verifyBoolQuestion(question->answer, optionAnswer);
          break;
      }

      if(correct){
        printf("Correct!\n");
        saveCursor();
        if(playerCurrentTile(order[id]) + numberOfSpaces < getBoardLength()){
          drawPlayer(order[id], playerCurrentTile(order[id]) + numberOfSpaces);
        }else{
          drawPlayer(order[id], getBoardLength());
          gameover = true;
          printf("%s WON!\n", getPlayerName(order[id]));
          printf("%d points", playerCurrentTile(order[id])-1);
          break;
        }
      }else{
        printf("Wrong!\n");
        saveCursor();
        if(playerCurrentTile(order[id]) - numberOfSpaces > 0){
          drawPlayer(order[id], playerCurrentTile(order[id]) - numberOfSpaces);
        }else{
          drawPlayer(order[id], 1);
        }
      }

      restoreCursor();
      waitInput("Press any key to continue...");
    }

  }while(!gameover);

  moveCursor(0,cursorYposition);
  waitInput("Press any key to continue...");

  freeQuestionList(boolQuestionList);
  freeQuestionList(multipleChoiceQuestionList);
}
