#include "menus.h"

void multipleChoicePage(){
  int id = 1, option = 0;

  Questions question;
  do{
    clearConsole();
    renderTitle("True or False Questions");
    int numQuestions = getNumberMultipleChoiceQuestions();
    printf("Number of True or False Questions: %d\n\n", numQuestions);

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
      addNewMultipleChoiceQuestion(question);
      option = 0;
    }

    if(option == -2) {
      deleteMultipleChoiceQuestion(id);
      option = 0;
    }

    if(option == -3) {
      editMultipleChoiceQuestion(id, question);
    }

    if(option >= 1 && option <= numQuestions)
      id = option;
  }while(option != 0);
}


void boolPage(){
  int id = 1, option = 0;

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
      addNewBoolQuestion(question);
      option = 0;
    }

    if(option == -2) {
      deleteBoolQuestion(id);
      option = 0;
    }

    if(option == -3) {
      editBoolQuestion(id, question);
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
      {"Direct Answer Questions", multipleChoicePage},
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
      printf("Admin %d\n", id);
      printf("Username: %s\n", admin.username);
      printf("Password: %s\n", admin.password);

      option = pageControls(&id, numAdmins);

      if(option == -1) {
        addNewAdmin(id);
        option = 0;
      }

      if(option == -2 && (id != currentLogin && id != 1)) {
        deleteAdmin(id);
        option = 0;
      }else if(option == -2){
        if(id == currentLogin){
          printf("Currently logged in. Cant delete this account");
        } else if(id == 1){
          printf("Root Admin cant be deleted");
        }

        waitInput("\nPress any key to continue...");
      }

      if(option == -3) {
        editAdmin(id);
      }

      if(option >= 1 && option <= numAdmins)
        id = option;
    }while(option != 0);
  }
}

void settings(){
  clearConsole();

  int selection;

  do{
    MenuOptions options[] = {
      {"Admins", adminPage},
      {"Questions", questionMenu},
      {"Boards", adminPage},
      {"Games", adminPage},
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
