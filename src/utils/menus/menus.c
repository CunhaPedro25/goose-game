#include "menus.h"

void multipleChoicePage(){
  int id = 1, option = 0, number;

  Questions question;
  do{
    clearConsole();
    renderTitle("Multiple Choice Questions");
    int numQuestions = getNumberMultipleChoiceQuestions();
    printf("Number of Multiple Choice Questions: %d\n\n", numQuestions);

    getMultipleChoiceQuestion(&question, id);
    setTextColor(BLUE, 1);
    printf("Question %d\n\n", id);
    resetColor();

    printf("Question: %s\n\n", question.question);
    setTextColor(GREEN, 1);
    printf("Correct Answer: %s\n", question.answer);
    setTextColor(RED, 1);
    for(int i = 0; i < 3; i++){
      printf("Wrong Answer %d: %s\n", i+1, question.wrongAnswers[i]);
    }
    resetColor();

    option = pageControls(&id, numQuestions);

    if(option == -1) {
      if(loginAdmin() != 0){
        clearConsole();
        printf("New Written Question\n");
        printf("Question: ");
        getString(question.question, 500);
        printf("Answer: ");
        getString(question.answer, 100);
        for(int i = 0; i < 3; i++){
          printf("Wrong Answer %d: ", i+1);
          getString(question.wrongAnswers[i], 100);
        }

        addNewMultipleChoiceQuestion(question);
        option = 0;
      }
    }

    if(option == -2) {
      if(loginAdmin() != 0){
        deleteMultipleChoiceQuestion(id);
        option = 0;
      }
    }

    if(option == -3) {
      if(loginAdmin() != 0){
        clearConsole();
        printf("Choose what's being edited\n");
        printf("\n1 - Question\n2 - Correct Answer\n3 - Wrong Answers");
        printf("\n> ");
        getNumberFromRange(&number, 1, 3);
        if(number == 1){
          printf("Question: ");
          getString(question.question, 500);
        }else if(number == 2){
          printf("Correct Answer: ");
          getString(question.answer, 100);
        }else{
          printf("Choose what's being edited\n");
          printf("\n1 - %s\n2 - %s\n3 - %s", question.wrongAnswers[0], question.wrongAnswers[1], question.wrongAnswers[2]);
          printf("\n> ");
          getNumberFromRange(&number, 1, 3);
          printf("New wrong Answer: ");
          getString(question.wrongAnswers[number-1], 100);
        }

        editMultipleChoiceQuestion(id, question);
      }
    }


    if(option >= 1 && option <= numQuestions)
      id = option;
  }while(option != 0);
}

void writtenPage(){
  int id = 1, option = 0, number;

  Questions question;
  do{
    clearConsole();
    renderTitle("Direct Answer Questions");
    int numQuestions = getNumberWrittenQuestions();
    printf("Number of Direct Answer Questions: %d\n\n", numQuestions);

    getWrittenQuestion(&question, id);
    setTextColor(BLUE, 1);
    printf("Question %d\n\n", id);
    resetColor();

    printf("Question: %s\n", question.question);
    printf("Answer: %s\n", question.answer);

    option = pageControls(&id, numQuestions);

    if(option == -1) {
      if(loginAdmin() != 0){
        clearConsole();
        printf("New Direct Answer Question\n");
        printf("Question: ");
        getString(question.question, 500);
        printf("Answer: ");
        getString(question.answer, 100);

        addNewWrittenQuestion(question);
        option = 0;
      }
    }

    if(option == -2) {
      if(loginAdmin() != 0){
        deleteWrittenQuestion(id);
        option = 0;
      }
    }

    if(option == -3) {
      if(loginAdmin() != 0){
        clearConsole();
        printf("Choose what's being edited\n");
        printf("\n1 - Question\n2 - Answer\n");
        printf("\n> ");
        getNumberFromRange(&number, 1, 2);
        if(number == 1){
          printf("Question: ");
          getString(question.question, 500);
        }else{
          printf("Answer: ");
          getString(question.answer, 100);
        }

        editWrittenQuestion(id, question);
      }
    }

    if(option >= 1 && option <= numQuestions)
      id = option;
  }while(option != 0);
}

void boolPage(){
  int id = 1, option = 0, number;

  Questions question;
  do{
    clearConsole();
    renderTitle("True or False Questions");
    int numQuestions = getNumberBoolQuestions();
    printf("Number of True or False Questions: %d\n\n", numQuestions);

    getBoolQuestion(&question, id);
    setTextColor(BLUE, 1);
    printf("Question %d\n\n", id);
    resetColor();

    printf("Question: %s\n\n", question.question);

    setTextColor(strcmp(question.answer, "True") == 0 ? GREEN : RED , 1);
    printf("Answer: %s\n", question.answer);
    resetColor();

    option = pageControls(&id, numQuestions);

    if(option == -1) {
      if(loginAdmin() != 0){
        clearConsole();
        printf("New true or False Question\n");
        printf("Question: ");
        getString(question.question, 500);
        printf("Answer:\n1 - True\n2 - False\n");
        printf("\n> ");
        getNumberFromRange(&number, 1, 2);
        strcpy(question.answer, number == 1 ? "True" : "False");

        addNewBoolQuestion(question);
        option = 0;
      }
    }

    if(option == -2) {
      if(loginAdmin() != 0){
        deleteBoolQuestion(id);
        option = 0;
      }
    }

    if(option == -3) {
      if(loginAdmin() != 0){
        clearConsole();
        printf("Choose what's being edited\n");
        printf("\n1 - Question\n2 - Answer\n");
        printf("\n> ");
        getNumberFromRange(&number, 1, 2);
        if(number == 1){
          printf("Question: ");
          getString(question.question, 500);
        }else{
          printf("Answer:\n1 - True\n2 - False\n");
          printf("\n> ");
          getNumberFromRange(&number, 1, 2);
          strcpy(question.answer, number == 1 ? "True" : "False");
        }

        editBoolQuestion(id, question);
      }
    }

    if(option >= 1 && option <= numQuestions)
      id = option;
  }while(option != 0);
}

void questionMenu(){
  clearConsole();

  int selection;

  do{
    MenuOptions options[] = {
      {"True or False Questions", boolPage},
      {"Multiple Choice Questions", multipleChoicePage},
      {"Direct Answer Questions", writtenPage},
    };

    selection = menu("Settings", options, sizeof(options)/sizeof(options[0]), "other");

    if(selection != 0) options[selection-1].callback();
  }while(selection != 0);
}

void adminPage(){
  int currentLogin = loginAdmin();

  if(currentLogin != 0){
    int id = 1, option = 0;

    Admins admin;
    do{
      clearConsole();
      renderTitle("Admin Page");
      int numAdmins = getNumberAdmins();
      printf("Current Login: Admin %d\n", currentLogin);
      printf("Numer of Admins: %d\n\n", numAdmins);

      getAdmin(&admin, id);
      setTextColor(BLUE, 1);
      printf("Admin %d\n\n", id);
      resetColor();

      printf("Username: %s\n", admin.username);
      printf("Password: %s\n", admin.password);

      option = pageControls(&id, numAdmins);

      if(option == -1) {
        addNewAdmin(id);
        option = 0;
      }

      if(option == -2 && (id != currentLogin && id != 1)) {
        if(id == currentLogin){
          printf("Currently logged in. Cant delete this account");
          waitInput("\nPress any key to continue...");
        } else if(id == 1){
          printf("Root Admin cant be deleted");
          waitInput("\nPress any key to continue...");
        }else{
          deleteAdmin(id);
          option = 0;
        }
      }

      if(option == -3) {
        editAdmin(id);
      }

      if(option >= 1 && option <= numAdmins)
        id = option;
    }while(option != 0);
  }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

#include <string.h>

int compareDates(const char* date1, const char* date2) {
    // Extract day, month, and year from date1
    char day1[3];
    char month1[3];
    char year1[5];
    strncpy(day1, date1, 2);
    day1[2] = '\0';
    strncpy(month1, date1 + 3, 2);
    month1[2] = '\0';
    strncpy(year1, date1 + 6, 4);
    year1[4] = '\0';

    // Extract day, month, and year from date2
    char day2[3];
    char month2[3];
    char year2[5];
    strncpy(day2, date2, 2);
    day2[2] = '\0';
    strncpy(month2, date2 + 3, 2);
    month2[2] = '\0';
    strncpy(year2, date2 + 6, 4);
    year2[4] = '\0';

    // Compare years
    if (strcmp(year1, year2) < 0) {
        return -1; // date1 is earlier
    } else if (strcmp(year1, year2) > 0) {
        return 1; // date2 is earlier
    }

    // Compare months
    if (strcmp(month1, month2) < 0) {
        return -1; // date1 is earlier
    } else if (strcmp(month1, month2) > 0) {
        return 1; // date2 is earlier
    }

    // Compare days
    if (strcmp(day1, day2) < 0) {
        return -1; // date1 is earlier
    } else if (strcmp(day1, day2) > 0) {
        return 1; // date2 is earlier
    }

    return 0; // dates are equal
}



void sortByNumPlayersASC(int *order, int maxGames){
  Games* games = (Games*) malloc(maxGames * sizeof(Games));
  getAllGames(games, maxGames);

  for (int i = 0; i < maxGames - 1; i++) {
      int minIndex = i;
      int minNumPlayers = games[order[i]].numberOfPlayers;

      for (int j = i + 1; j < maxGames; j++) {
          int currNumPlayers = games[order[j]].numberOfPlayers;
          if (currNumPlayers < minNumPlayers) {
              minIndex = j;
              minNumPlayers = currNumPlayers;
          }
      }

      if (minIndex != i) {
          swap(&order[i], &order[minIndex]);
      }
  }

  free(games);
}

void sortByNumPlayersDESC(int *order, int maxGames) {
  Games* games = (Games*) malloc(maxGames * sizeof(Games));
  getAllGames(games, maxGames);

  for (int i = 0; i < maxGames - 1; i++) {
      int maxIndex = i;
      for (int j = i + 1; j < maxGames; j++) {
          if (games[order[j]].numberOfPlayers > games[order[maxIndex]].numberOfPlayers) {
              maxIndex = j;
          }
      }
      if (maxIndex != i) {
          swap(&order[i], &order[maxIndex]);
      }
  }

  free(games);
}

void sortByDateASC(int *order, int maxGames) {
    Games* games = (Games*) malloc(maxGames * sizeof(Games));
    getAllGames(games, maxGames);

    for (int i = 0; i < maxGames - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < maxGames; j++) {
            if (compareDates(games[order[j]].date, games[order[minIndex]].date) < 0) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(&order[i], &order[minIndex]);
        }
    }

    free(games);
}

void sortByDateDESC(int *order, int maxGames) {
    Games* games = (Games*) malloc(maxGames * sizeof(Games));
    getAllGames(games, maxGames);

    for (int i = 0; i < maxGames - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < maxGames; j++) {
            if (compareDates(games[order[j]].date, games[order[maxIndex]].date) > 0) {
                maxIndex = j;
            }
        }
        if (maxIndex != i) {
            swap(&order[i], &order[maxIndex]);
        }
    }

    free(games);
}

void gamesTable(){
  int option;
  int numSavedGames = getMaxGamesSaved();
  int size = numSavedGames < 5 ? numSavedGames : 5;

  int *order = (int *) malloc(numSavedGames * sizeof(int));
  for(int i = 0; i < numSavedGames; i++){
    order[i] = i;
  }

  do {
    clearConsole();
    renderTitle("All Games Played");

    char *keys = " id | N Players |  Player 1  |  Player 2  |  Player 3  |  Player 4  |  Date DD/MM/YY  " ;
    int tableSize = (int)strlen_utf8(keys) + 2;

    printf("\n");
    for(int i = 0; i < tableSize; i++){
      printf("-");
    }
    printf("\n");

    printf("|%s|", keys);

    printf("\n");
    for(int i = 0; i < tableSize; i++){
      printf("-");
    }
    printf("\n");

    Games game;
    memset(&game, 0, sizeof(Games));
    if(numSavedGames > 0){
      char temp[100];
      int startingSize = (size-5 < 0 ? 0 : (size == numSavedGames && (numSavedGames % 5) != 0 ? size-(numSavedGames % 5) : size-5));
      for(int i = startingSize; i < size; i++){
        getGameInfo(&game, order[i]);

        printf("| %2d ", order[i]+1);  // id

        printf("|     %d     ", game.numberOfPlayers);

        for(int j = 0; j < 4; j++){
          if(j < game.numberOfPlayers){
            printf("|");
            setTextColor(game.players[j].color, 1);
            printf("  %-*s  ", (int)strlen_utf8("Player 1"), game.players[j].name);
            resetColor();
          }else{
            printf("|  --------  ");
          }

        }
        printf("|   %s   |\n", game.date);
      }


      for(int i = 0; i < tableSize; i++){
        printf("-");
      }
      printf("\n");
    }else{
      moveCursor(tableSize/2 - (int)(strlen_utf8("Sem equipamentos")/2), 9);
      printf("Sem Jogos\n");
    }

    option = tableControls(&size, numSavedGames, tableSize);

    if(option == 1){
      MenuOptions options[] = {
        {"By Number of Players Ascending"},
        {"By Number of Players Descending"},
        {"By Date Ascending"},
        {"By Date Descending"},
      };

      int selection = menu("Sort", options, sizeof(options)/sizeof(options[0]), "other");

      switch(selection){
        case 1:
          sortByNumPlayersASC(order, numSavedGames);
          break;
        case 2:
          sortByNumPlayersDESC(order, numSavedGames);
          break;
        case 3:
          sortByDateASC(order, numSavedGames);
          break;
        case 4:
          sortByDateDESC(order, numSavedGames);
          break;
      }
    }
  } while (option != 0);

  free(order);
}

void settings(){
  clearConsole();

  int selection;

  do{
    MenuOptions options[] = {
      {"Admins", adminPage},
      {"Questions", questionMenu},
      {"Games", gamesTable},
    };

    selection = menu("Settings", options, sizeof(options)/sizeof(options[0]), "other");

    if(selection != 0) options[selection-1].callback();
  }while(selection != 0);
}


int menu(char *title, MenuOptions *options, size_t size, char *type){
  int option = -1;

  clearConsole();
  renderTitle(title);

  for (int i = 0; i < size; ++i) {
    printf("    [%d] %s\n", i+1, options[i].name);
  }
  printf("    [Q] %s", strcmp(type, "main") ? "Back" : "Exit");

  printf("\n\n");
  printf(">");
  do {
    char temporary[10];

    getString(temporary, 10);

    if(strcmp(temporary, "q") == 0 || strcmp(temporary, "Q") == 0 ){
      return 0;
    }

    if(!isInt(temporary)){
      showSpecificInvalidOption("[Invalid Option]");
      continue;
    }

    char *trash;
    option = strtol(temporary, &trash, 10);

    if(option < 1 || option > size) {
      showSpecificInvalidOption("[Invalid Option]");
    }
  } while (option < 1 || option > size);

  return option;
}
