#include "menus.h"

int menu(char *title, MenuOptions *options, size_t size, char *type){
  int option = -1;

  clearConsole();
  renderTitle(title);

  for (int i = 0; i < size; ++i) {
    printf("    [%d] %s\n", i+1, options[i].name);
  }
  printf("    [s] %s", strcmp(type, "main") ? "Voltar" : "Sair");

  printf("\n\n");
  printf(">");
  do {
    char temporary[10];

    getString(temporary, 10);

    if(strcmp(temporary, "s") == 0 || strcmp(temporary, "S") == 0 ){
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
