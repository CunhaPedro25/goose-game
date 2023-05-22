#ifndef UI_H
#define UI_H

#include <stdio.h>

typedef enum {
  BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
} Color;

void moveCursor(int x, int y);
void clearConsole();
void clearToScreenEnd();
void clearToScreenStart();

void clearToLineEnd();
void clearToLineStart();

void clearLine();

void setTextColor(int color, int bright);
void setBackgroundColor(int color, int bright);
void resetColor();

#endif /* UI_H */
