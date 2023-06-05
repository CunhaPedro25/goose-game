#include "pages.h"

int validNumber(char *option, int maxID){
  int value;
  char *trash;
  value = strtol(option, &trash, 10);

  if(strlen(trash) > 1) return false;

  if(value < 1 || value > maxID) {
    showSpecificInvalidOption("[Invalid Option]");
    return false;
  }

  return value;
}

int validPagesOption(char *option, int *id, int maxID){
  if(isInt(option)){
    return validNumber(option, maxID);
  }

  if(option[1] == '\0') {
    switch (option[0]) {
      /*Previous Page*/
      case 'a':
      case 'A':
        if (*id-1 > 0) {
          *id -= 1;
          return  true;
        }
        showSpecificInvalidOption("");
        return false;
      /*Next Page*/
      case 'd':
      case 'D':
        if (*id+1 <= maxID) {
          *id += 1;
          return  true;
        }
        showSpecificInvalidOption("");
        return false;
      /*Create*/
      case 'w':
      case 'W':
      /*Edit*/
      case 'e':
      case 'E':
      /*Remove*/
      case 'r':
      case 'R':
      /*Search*/
      case 's':
      case 'S':
      /*Leave*/
      case 'q':
      case 'Q':
        return true;

      default:
        break;
    }
  }

  showSpecificInvalidOption("[Invalid Option]");
  return false;
}


int pageControls(int *id, int maxID){
  char option[10];

  char *functions = " Search [S] Create [W] Edit [E]  Remove [R]  Other <id>  Quit [Q] ";
  int lineSize = (int) strlen(functions);

  /* Render functions for table */
  printf("\n");
  for(int i = 0; i < lineSize; i++){
    printf("-");
  }
  printf("\n");
  printf("%s", functions);

  /* Page Control */
  printf("\n%s", *id-1 > 0 ? "< A " : "----");
  for(int i = 0; i < lineSize-8; i++){
    printf("-");
  }
  printf("%s\n", *id+1 <= maxID ? " D >" : "----");

  printf("\n> ");
  do{
    getString(option, 100);
  }while(!validPagesOption(option, id, maxID));

  if(strcmp(option, "q") == 0 || strcmp(option, "Q") == 0){
    return 0;
  }

  if((strcmp(option, "w") == 0 || strcmp(option, "W") == 0) && maxID > 0){
    return -1;    // Code to detect that its in create menu
  }

  if((strcmp(option, "r") == 0 || strcmp(option, "R") == 0) && maxID > 0){
    char confirm[2];
    if (askConfirmation("Are you sure you want to delete"))
      return -2;    // Code to detect that its in deleteing menu
  }

  if((strcmp(option, "e") == 0 || strcmp(option, "E") == 0) && maxID > 0){
    return -3;    // Code to detect that its in edit menu
  }

  if((strcmp(option, "s") == 0 || strcmp(option, "S") == 0) && maxID > 0){
    return -4;    // Code to detect that its in edit menu
  }

  /* Check if it's a number and return its value if true (0 - MaxID) */
  if(isInt(option)) {
    return validNumber(option, maxID);
  }

  return -10;  // The return value is -10 to not break the while loop from the original fucntion (0 - leave menu)
}
