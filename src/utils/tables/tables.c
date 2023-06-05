#include "tables.h"

int validTableOption(char *option, int *size, int maxID){
  if(option[1] == '\0') {
    switch (option[0]) {
      case 'a':
      case 'A':
        if (*size-5 > 0) {
          *size -= (maxID == *size && maxID % 5 != 0) ? *size%5 : 5;
          return  true;
        }
        restoreCursor();
        clearToScreenEnd();
        return false;
      case 'd':
      case 'D':
        if(maxID == 0 || *size == maxID){
          restoreCursor();
          clearToScreenEnd();
          return false;
        }

        if (*size+5 <= maxID) {
          *size += 5;
          return  true;
        }else if(*size - maxID < 5){
          *size = maxID;
          return  true;
        }
        restoreCursor();
        clearToScreenEnd();
        return false;
      /*SORT*/
      case 's':
      case 'S':
      /*EXIT*/
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


int tableControls(int *size, int maxID, int lineSize){
  char option[10];
  char functionsText[2][20] = {
      " Sort [S] ",
      "Exit [Q] "
  };
  int fucntionLineSize = 0;
  for(int i = 0; i < 2; i++){
    fucntionLineSize += (int)strlen_utf8(functionsText[i]);
  }
  lineSize = lineSize < fucntionLineSize ? fucntionLineSize : lineSize;
  int spacesBetween = 0;

  moveCursor(0,13);

  printf("\n");
  for(int i = 0; i < lineSize; i++){
    printf("-");
  }
  printf("\n");

  /* Render fucntions for table */
  for(int i = 0; i < 2; i++){
    printf("%s", functionsText[i]);

    if(i != 1) {
      int extraText = (int) (strlen_utf8(functionsText[i]) + strlen(functionsText[i+1]));
      spacesBetween = lineSize - extraText;
      for (int j = 0; j < spacesBetween; j++) {
        printf(" ");
      }
    }
  }

  /* Page Control */
  printf("\n%s", *size-5 > 0 ? "< A " : "----");
  for(int i = 0; i < lineSize-8; i++){
    printf("-");
  }
  printf("%s\n", *size+5 <= maxID ? " D >" : "----");

  printf("\n> ");
  saveCursor();
  do{
    getString(option, 10);
  }while(!validTableOption(option, size, maxID));

  if((option[0] == 'q' || option[0] == 'Q')){
    return 0;
  }

  if((option[0] == 's' || option[0] == 'S')){
    return 1;
  }

  return -1;  // The return value is -1 to not break the while loop from the original fucntion (0 - leave menu)
}
