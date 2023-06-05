#include "game.h"

#define FILE_PATH_LENGTH 256
#define EXTRA_PATH_LENGTH 512

#ifdef _WIN32
    #define PLATFORM_PATH_ENV "LOCALAPPDATA"
    #define PLATFORM_FOLDER "gooseGame\\games\\"
#elif __linux__
    #define PLATFORM_PATH_ENV "HOME"
    #define PLATFORM_FOLDER ".gooseGame/games/"
#elif __APPLE__
    #define PLATFORM_PATH_ENV "HOME"
    #define PLATFORM_FOLDER "Applications/gooseGame/games/"
#endif

void getAllGames(Games* games, int maxGames){
  char platformPath[FILE_PATH_LENGTH];
  getPlatformFilePath(platformPath, PLATFORM_PATH_ENV, PLATFORM_FOLDER);

  char fullPath[EXTRA_PATH_LENGTH];
  sprintf(fullPath, "%s%s", platformPath, "allGames.dat");
  FILE *file = fopen(fullPath, "rb");
  if(file == NULL){
    return;
  }

  long int position = sizeof(int);

  fseek(file, position, SEEK_SET);

  fread(games, sizeof(Games), maxGames, file);

  fclose(file);
}

int getMaxGamesSaved(){
  char platformPath[FILE_PATH_LENGTH];
  getPlatformFilePath(platformPath, PLATFORM_PATH_ENV, PLATFORM_FOLDER);

  char fullPath[EXTRA_PATH_LENGTH];
  sprintf(fullPath, "%s%s", platformPath, "allGames.dat");
  FILE *file = fopen(fullPath, "rb");
  if(file == NULL){
    return 0;
  }

  int numOfGames;
  fread(&numOfGames, sizeof(int), 1, file);

  fclose(file);
  return numOfGames;
}

void getGameInfo(Games* game, int id){
  char platformPath[FILE_PATH_LENGTH];
  getPlatformFilePath(platformPath, PLATFORM_PATH_ENV, PLATFORM_FOLDER);

  char fullPath[EXTRA_PATH_LENGTH];
  sprintf(fullPath, "%s%s", platformPath, "allGames.dat");
  FILE *file = fopen(fullPath, "rb+");
  if(file == NULL){
    return;
  }

  long int position = sizeof(int) + id * sizeof(Games);

  // Move the file pointer to the calculated position
  fseek(file, position, SEEK_SET);

  fread(game, sizeof(Games), 1, file);

  fclose(file);
}

void saveGameToDB(int numPlayers){
  char platformPath[FILE_PATH_LENGTH];
  getPlatformFilePath(platformPath, PLATFORM_PATH_ENV, PLATFORM_FOLDER);

  char fullPath[EXTRA_PATH_LENGTH];
  sprintf(fullPath, "%s%s", platformPath, "allGames.dat");
  FILE *file = fopen(fullPath, "rb+");
  if(file == NULL){
    return;
  }

  int numOfGames;
  fread(&numOfGames, sizeof(int), 1, file);
  numOfGames++;
  fseek(file, 0, SEEK_SET);
  fwrite(&numOfGames, sizeof(int), 1, file);


  Games game;
  memset(&game, 0, sizeof(Games));

  game.numberOfPlayers = numPlayers;
  Player tempPlayer;
  for(int i = 0; i < numPlayers; i++){
    getPlayer(&tempPlayer, i);
    game.players[i] = tempPlayer;
  }
  currentDate(game.date);

  fseek(file, 0, SEEK_END);
  fwrite(&game, sizeof(Games), 1, file);

  fclose(file);
}


/* LIVE GAME FUNCTIONS*/

int initializeGame(QuestionNode** boolQuestionList, QuestionNode** multipleChoiceQuestionList, QuestionNode** writtenQuestionList){
  int numPlayers;
  char name[100];
  int number;

  clearConsole();
  printf("How many players are in the game? (Min: 2; Max: 4)\n");
  printf("> ");
  getNumberFromRange(&numPlayers, 2, 4);

  createPlayers(numPlayers);

  for(int i = 0; i < numPlayers; i++){
    clearConsole();

    printf("Player %d name\n", i+1);
    printf("> ");
    do{
      saveCursor();
      getString(name, 100);
      savePlayerName(i, name);
    }while(isNameTaken(name, i));

    do{
      printf("\nPlayer color:\n");
      if(!isColorTaken(RED, i)){
        setTextColor(RED, 1);
        printf("1 - RED\n");
      }

      if(!isColorTaken(GREEN, i)){
        setTextColor(GREEN, 1);
        printf("2 - GREEN\n");
      }

      if(!isColorTaken(YELLOW, i)){
        setTextColor(YELLOW, 1);
        printf("3 - YELLOW\n");
      }

      if(!isColorTaken(BLUE, i)){
        setTextColor(BLUE, 1);
        printf("4 - BLUE\n");
      }

      resetColor();
      printf("> ");
      getNumberFromRange(&number, 1,4);
      moveCursor(0,3);
      clearToScreenEnd();
    }while(isColorTaken(number, i));

    savePlayerColor(i, number);
  }

  storeRandomizedBoolQuestions(boolQuestionList);
  storeRandomizedMultipleChoiceQuestions(multipleChoiceQuestionList);
  storeRandomizedWrittenQuestions(writtenQuestionList);

  getBoardsInFolder();

  clearConsole();
  drawBoard();

  for(int id = 0; id < numPlayers; id++){
    drawPlayer(id,1);
  }

  return numPlayers;
}

void determinePlayerOrder(int *order, int numPlayers){
    int *dice = (int *) malloc(numPlayers * sizeof(int));
    if (dice == NULL) {
        // Error handling for memory allocation failure
        printf("Error: Memory allocation failed for dice array.\n");
        return;
    }

    int cursorYposition = (getBoardMaxHeight()+2) * 3 + 1;  //Covert to screen position (screen_y = y * 3 + 1)

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
  QuestionNode* writtenQuestionList = NULL;

  // Call function to ask for numPlayers, create map, and draw players
  int numPlayers = initializeGame(&boolQuestionList, &multipleChoiceQuestionList, &writtenQuestionList);

  int *order = (int *) malloc(numPlayers * sizeof(int));
  if (order == NULL) {
      // Error handling for memory allocation failure
      printf("Error: Memory allocation failed for order array.\n");
      return;
  }

  determinePlayerOrder(order, numPlayers);

  bool gameover = false;
  int numberOfSpaces;
  int optionAnswer = 0;
  char writtenAnswer[100];
  int cursorYposition = (getBoardMaxHeight()+2) * 3 + 1;  //Covert to screen position (screen_y = y * 3 + 1)
  Questions question;


  do{
    for(int id = 0; id < numPlayers; id++){
      moveCursor(0,cursorYposition);
      clearToScreenEnd();

      bool correct = false;
      numberOfSpaces = rand() % 6 + 1;

      printf("%s's turn | Points: %2d \n", getPlayerName(order[id]), playerCurrentTile(order[id])-1);
      printf("Question Type: %d | Question Points: +%d\n\n", getGameTileType(playerCurrentTile(order[id])), numberOfSpaces);

      switch(getGameTileType(playerCurrentTile(order[id]))){
        case TRUEFALSE:
            if(getQuestionFromList(&boolQuestionList, &question)){
              printf("Question: %s\n", question.question);
              printf("1 - True\n2 - False\n");

              printf("\n> ");
              getNumberFromRange(&optionAnswer, 1,2);
              correct = verifyBoolQuestion(question.answer, optionAnswer);
            }else{
              gameover = true;
              char* lines[] = {
                "Game Over!",
                "No more True or False Questions"
              };
              int numLines = sizeof(lines) / sizeof(lines[0]);

              writeOnBoardCenter(lines, numLines);
            }
          break;
        case MULTIPLE:
            if(getQuestionFromList(&multipleChoiceQuestionList, &question)){
              printf("Question: %s\n", question.question);

              int correctIndex = getCorrectAnswerIndex(question.answer, question.wrongAnswers);

              printf("\n> ");
              getNumberFromRange(&optionAnswer, 1,4);

              correct = (optionAnswer == correctIndex);
            }else{
              gameover = true;
              char* lines[] = {
                "Game Over!",
                "No more Multiple Choice Questions"
              };
              int numLines = sizeof(lines) / sizeof(lines[0]);

              writeOnBoardCenter(lines, numLines);
            }
          break;
        case WRITTEN:
            if(getQuestionFromList(&writtenQuestionList, &question)){
            printf("Question: %s\n", question.question);

              printf("> ");
              getString(writtenAnswer, 100);
              correct = strcasecmp(question.answer, writtenAnswer) == 0;
            }else{
              gameover = true;
              char* lines[] = {
                "Game Over!",
                "No more Direct Answer Questions"
              };
              int numLines = sizeof(lines) / sizeof(lines[0]);

              writeOnBoardCenter(lines, numLines);
            }
          break;
      }

      if(gameover) break;


      if(correct){
        printf("Correct!\n\n");
        saveCursor();
        if(playerCurrentTile(order[id]) + numberOfSpaces < getBoardLength()){
          drawPlayer(order[id], playerCurrentTile(order[id]) + numberOfSpaces);
        }else{
          drawPlayer(order[id], getBoardLength());
          moveCursor(0,cursorYposition);
          clearToScreenEnd();
          gameover = true;


          char playerWonString[100];
          snprintf(playerWonString, sizeof(playerWonString), "%s Won!", getPlayerName(order[id]));

          char* lines[] = {
            "Game Over!",
            playerWonString
          };
          int numLines = sizeof(lines) / sizeof(lines[0]);

          writeOnBoardCenter(lines, numLines);
          break;
        }
      }else{
        printf("Wrong!\n");

        if(getGameTileType(playerCurrentTile(order[id])) != TRUEFALSE){
          printf("Correct Answer: %s\n\n", question.answer);
        }
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

  printf("%d", numPlayers);
  waitInput("...");
  saveGameToDB(numPlayers);

  free(order);
  freeQuestionList(boolQuestionList);
  freeQuestionList(multipleChoiceQuestionList);
  freeQuestionList(writtenQuestionList);
  freePlayers();
  freeBoard();
}
