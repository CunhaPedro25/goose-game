#ifndef MENUS_H
#define MENUS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../ui/ui.h"
#include "../functions/functions.h"
#include "../pages/pages.h"

typedef void (*Callback)();

typedef struct options{
  char *name;
 Callback callback;
}MenuOptions;


void settings();
int menu(char* title, MenuOptions *options, size_t size, char *type);

#endif //MENUS_H
