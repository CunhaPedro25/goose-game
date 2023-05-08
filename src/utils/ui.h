#ifndef UI_H
#define UI_H

#include <stdio.h>

typedef enum {
  BLACK,
  RED,
  GREEN
} Color;

void moveCursor(int x, int y);
void clearConsole();

#endif /* UI_H */
