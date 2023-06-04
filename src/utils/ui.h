#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <string.h>

#include "functions.h"

#define prefix "\e["

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

void saveCursor();
void restoreCursor();
void cursorVisibility(int state);

void clearConsole();
void clearToScreenEnd();
void clearToScreenStart();

void clearToLineEnd();
void clearToLineStart();

void clearLine();

void setTextColor(int color, int bright);
void setBackgroundColor(int color, int bright);
void resetColor();

void renderTitle(const char *title);

#endif /* UI_H */
