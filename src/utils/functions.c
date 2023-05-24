#include "functions.h"

void showSpecificInvalidOption(char *text){
  setTextColor(RED, false);
  clearToLineEnd();
  printf("%s", text);    // Show error message
  restoreCursor();
  clearToLineEnd();
}


void removeNewline(char *string){
  string[strcspn(string, "\n")] = 0;
}

size_t strlen_utf8(const char *string) {
  size_t count = 0;
  while (*string) {
    count += (*string++ & 0xC0) != 0x80;
  }
  return count;
}

//Checks for int type in string by finding char that are not digits
bool isInt(char *text){
  for(int i = 0; i < strlen_utf8(text); i++){
    if(!isdigit(text[i])){
      return false;
    }
  }
  return true;
}

bool isEmpty(char *text){
  if(strcmp(text, "") == 0) return true;
  for (int i = 0; i < strlen_utf8(text); ++i) {
    if(text[i] != ' '){
      return false;
    }
  }

  return true;
}

//Custom read func for strings that requires a valid input to be met
bool getString(char *string, int maxInputSize){
  do {
    saveCursor();
    fgets(string, maxInputSize, stdin);
    removeNewline(string);

    if(isEmpty(string))
      showSpecificInvalidOption("[Invalid Option]");
  }while (isEmpty(string));

  return true;
}

//Custom read func for ints that requires a valid input to be met
bool getNumber(int *number, int maxInputSize){
  char *tempString = NULL;
  tempString = (char *) malloc(maxInputSize * sizeof(char));
  char *trash;
  do {
    getString(tempString, maxInputSize);
    if (isInt(tempString) == false) {
      showSpecificInvalidOption("[Invalid Option]");
    }
  }while (isInt(tempString) == false);
  *number = strtol(tempString, &trash, 10);

  return true;
}


bool getNumberFromRange(int *answer, int min, int max){
    do {
        getNumber(answer, 100);
        if(*answer < min || *answer > max) {
            showSpecificInvalidOption("[Invalid Option]");
        }
    }while(*answer < min || *answer > max);

    return true;
}
