/*
 *name: pong_ardu.ino
 *version: 0.0.1
 *description: Pong gamed based on the max7221lib.h, played on 4x64 led matrix with 4 max7221-ic's daisychained
 *authors: Richard Walter, Franz Huebner
 *web:
*/
int potPinP1ay1 = 2;      //input pin for player 1s potentiometer
int potPinP1ay2 = 3;      //input pin for player 2s potentiometer
int potVal1 = 0;          //store the value of player 1s poti
int potVal2 = 0;          //store the value of player 2s poti
boolean gamearea[16][16];

void setup() {
  for(int horiz = 0; horiz <= 8; horiz++){      //horizontral iterrieren
      for(int vert =0; vert <= 8; vert++){
        gamearea[horiz][vert]= false;
      }
  }
}

void clearColumn(int column){
  for(int i=3; i<=15; i++){
    gamearea[i][column]= false;
  }
}

//clear the matrix, 1 for complete Matrix / 2 for only Playground
void clearGamearea(int area){
  int i;
  switch(area){
    case 1: i=0;                
    case 2: i=3; 
  }
  for(int i=0; i<=15; i++){
    for(int j=0; j<=15; j++){
      gamearea[i][j]=false;
    }
  }
}


void winner(int Player){
  clearGamearea(2);  
  switch(Player){
      case 1: gamearea[15][0];
      case 2: gamearea[15][15];
  }
  
}

void potiControl(int value ,int column){
  if(value <= 0 && value <= 93){
    clearColumn;
    gamearea[15][column]=true;
    gamearea[14][column]=true;
    gamearea[13][column]=true;
  }
  else if(value <= 94 && value <= 186){
    clearColumn;
    gamearea[14][column]=true;
    gamearea[13][column]=true;
    gamearea[12][column]=true;
  }
  else if(value <= 187 && value <= 279){
    clearColumn;
    gamearea[13][column]=true;
    gamearea[12][column]=true;
    gamearea[11][column]=true;
  }
  else if(value <= 280 && value <= 372){
    clearColumn;
    gamearea[12][column]=true;
    gamearea[11][column]=true;
    gamearea[10][column]=true;
  }
  else if(value <= 373 && value <= 465){
    clearColumn;
    gamearea[11][column]=true;
    gamearea[10][column]=true;
    gamearea[9][column]=true;
  }
  else if(value <= 466 && value <= 558){
    clearColumn;
    gamearea[10][column]=true;
    gamearea[9][column]=true;
    gamearea[8][column]=true;
  }
  else if(value <= 559 && value <= 651){
    clearColumn;
    gamearea[9][column]=true;
    gamearea[8][column]=true;
    gamearea[7][column]=true;
  }
  else if(value <= 652 && value <= 744){
    clearColumn;
    gamearea[8][column]=true;
    gamearea[7][column]=true;
    gamearea[6][column]=true;
  }
  else if(value <= 745 && value <= 837){
    clearColumn;
    gamearea[7][column]=true;
    gamearea[6][column]=true;
    gamearea[5][column]=true;
  }
  else if(value <= 838 && value <= 930){
    clearColumn;
    gamearea[6][column]=true;
    gamearea[5][column]=true;
    gamearea[4][column]=true;
  }
  else if(value <= 931 && value <= 1023){
    clearColumn;
    gamearea[5][column]=true;
    gamearea[4][column]=true;
    gamearea[3][column]=true;
  }
}

void AddPointScoreboard(int Player){
  if(Player == 1){
    for(int i=0; i<=6; i++){
      if(!(gamearea[0][i])){
         gamearea[0][i] = true;
      }
      if(gamearea[0][6]){
        winner(1);
      }else{
        for(int i=15; i>=9; i--){
            if(!(gamearea[0][i])){
              gamearea[0][i] = true;
             }
            if(gamearea[0][6]){
            winner(2);
        
      }
    }
   } 
  }
  }
}


void loop() {
  // put your main code here, to run repeatedly:

  potVal1 = analogRead(potPinP1ay1);
  potVal2 = analogRead(potPinP1ay2);
  potiControl(potVal1, 1);
  potiControl(potVal2, 2);

  }
