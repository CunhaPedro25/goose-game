#ifndef MENUS_H
#define MENUS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ui.h"
#include "functions.h"

typedef void (*Callback)();

typedef struct options{
  char *name;
 Callback callback;
}MenuOptions;

int menu(char* title, MenuOptions *options, size_t size, char *type);

#endif //MENUS_H
