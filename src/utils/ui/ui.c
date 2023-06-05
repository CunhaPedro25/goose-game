#include "ui.h"

void moveCursor(int x, int y) { printf(prefix "%d;%dH", y, x);}

void saveCursor() { printf(prefix "s"); }
void restoreCursor() { printf(prefix "u"); }

void cursorVisibility(int state){
  if(state){
    printf(prefix "?25h");
  }else{
    printf(prefix "?25l");
  }
}

void clearConsole() { printf(prefix "2J\e[H");}
void clearToScreenEnd() { printf(prefix "0J"); }
void clearToScreenStart() { printf(prefix "1J"); }

void clearToLineEnd() { printf(prefix "0K"); }
void clearToLineStart() { printf(prefix "1K"); }

void clearLine() { printf(prefix "2K"); }

void setTextColor(int color, int bright){ printf(prefix "%dm", (bright ? 90 : 30) + color); }
void setBackgroundColor(int color, int bright){ printf(prefix "%dm", (bright ? 100 : 40) + color); }
void resetColor(){ printf(prefix "0m"); }
