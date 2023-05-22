#include "ui.h"

void moveCursor(int x, int y) { printf("\e[%d;%dH", y, x);}
void clearConsole() { printf("\e[2J\e[H");}
void clearToScreenEnd() { printf("\e[0J"); }
void clearToScreenStart() { printf("\e[1J"); }

void clearToLineEnd() { printf("\e[0K"); }
void clearToLineStart() { printf("\e[1K"); }

void clearLine() { printf("\e[2K"); }

void setTextColor(int color, int bright){ printf("\e[%dm", (bright ? 90 : 30) + color); }
void setBackgroundColor(int color, int bright){ printf("\e[%dm", (bright ? 100 : 40) + color); }
void resetColor(){ printf("\e[0m"); }
