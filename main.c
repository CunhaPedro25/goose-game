#include <stdio.h>

typedef struct tile{
  int x;
  int y;
  int type;
}Tile;

typedef struct player{
  int id;
  int currentTile;
}Player;

enum tileType{
  EMPTY,
  QUESTION,
};

enum color{
  BLACK,
  RED,
  GREEN
};

Tile tiles[8] = {
  {0,0,EMPTY},
  {0,1,EMPTY},   
  {0,2,QUESTION},
  {0,3,EMPTY},
  {1,3,EMPTY},
  {2,3,EMPTY},
  {3,3,EMPTY},
  {3,4,EMPTY},
};

Player players[4] = {
  {RED,0},
  {GREEN,0},
};

void moveCursor(int x, int y) { printf("\e[%d;%dH", y, x);}

void drawTile(int x, int y, int number){
  int new_x = y * 5 +1; 
  int new_y = x * 2 +1;

  moveCursor(new_x,new_y);

  if(number ==  8){
    printf("\e[7m|\e[27m \e[7m%d\e[27m.\e[7m \e[27m|", number);
    moveCursor(new_x,new_y+1);
    printf("|\e[7m \e[27m \e[7m \e[27m \e[7m|\e[27m");
    
  }else{
    printf("| %d. |", number);
    moveCursor(new_x,new_y+1);
    printf("|    |");
  }
}

void drawPlayer(int id, int tile){
  int oldTile = players[id-1].currentTile;
  int new_x = tiles[oldTile].y * 5 +1;
  int new_y = tiles[oldTile].x * 2 +1;

  moveCursor(new_x+players[id-1].id ,new_y+1);
  printf(" ");

  players[id-1].currentTile = tile-1;
  new_x = tiles[tile-1].y * 5 +1;
  new_y = tiles[tile-1].x * 2 +1;
  moveCursor(new_x+players[id-1].id ,new_y+1);
  printf("\e[%dm", 30+id);
  printf("o");
  printf("\e[%dm", 0);
}

int getNumber(){
  int selection = 0;

  scanf("%d", &selection);
  fflush(stdin);

  return selection;
}

int main(){

  // printf(" | 1. | 2. | 3. | 4. | 5. |");
  // printf(" |oooo|    |    |    |    |")

  
  printf("\e[2J");
  for (int i = 0; i < 8; i++){
    drawTile(tiles[i].x, tiles[i].y, i+1);
  }

  for (int i = 1; i < 2; i++){
    drawPlayer(i, 1);
  }

  int selection;
  do{
    moveCursor(0,10);
    printf("Select Tile >");
    drawPlayer(RED, selection = getNumber());
  }while(selection != 0);

  moveCursor(0,0);
  printf("\e[2J");


  return 0;
}