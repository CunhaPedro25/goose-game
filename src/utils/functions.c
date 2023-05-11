#include "functions.h"

int getNumber(){
  int selection = 0;

  scanf("%d", &selection);
  fflush(stdin);

  return selection;
}