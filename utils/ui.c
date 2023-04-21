#include "ui.h"

void moveCursor(int x, int y) { printf("\e[%d;%dH", y, x);}
void clearConsole() { printf("\e[2J\e[H");}
