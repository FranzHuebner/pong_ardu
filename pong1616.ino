

int potPinP1ay1 = A1;      //input pin for player 1s potentiometer
int potPinP1ay2 = A2;      //input pin for player 2s potentiometer
int potVal1 = 0;          //store the value of player 1s poti
int potVal2 = 0;          //store the value of player 2s poti
boolean gamearea[16][16]; //Array for the gamearea
boolean endOfGame = false;      //flag for the end of game state

struct ball               //struct for the ball
{
 int speedx;
 int speedy;
 int old_x;
 int old_y;
 int new_x;
 int new_y;
}pongBall;

struct bat                //struct for the bats of the two Players
{
  int column;
  int topPos;
  int midPos;
  int botPos;
}batPlay1 , batPlay2;

//Function that brings the ball at its init-position
void startAGame(){
  pongBall.new_x = 7;
  pongBall.new_y = 9;
  pongBall.speedx = 1;
  pongBall.speedy = 0;
}

//setup function that runs first
void setup() {


clearGamearea(1);
  startAGame();
  batPlay1.column = 1;
  batPlay2.column = 14;

}

// function to clear one collumn in the matrix
void clearColumn(int column){
  for(int i=1; i<=15; i++){
    gamearea[column][i]= false;
  }
}

//clear the matrix, 1 for complete matrix / 2 for only playground
void clearGamearea(int area){
  int j;
  switch(area){
    case 1: j=0;
    case 2: j=1;
  }
  for(int i=0; i<=15; i++){
    for(int k=15; j<=k; j++){
      gamearea[i][k]=false;
    }
  }
}

//function wich move the ball with x and y coordinate and a collison handler for the walls
void moveBall(){
  pongBall.old_x = pongBall.new_x;
  pongBall.old_y = pongBall.new_y;
  pongBall.new_x = pongBall.new_x + pongBall.speedx;
  pongBall.new_y = pongBall.new_y + pongBall.speedy;
  if(pongBall.new_y <= 3 ) pongBall.speedy = (pongBall.speedy)*-1;     //colision with top
  if(pongBall.new_y >=15 ) pongBall.speedy = (pongBall.speedy)*-1;    //colision with bottom
  gamearea[pongBall.new_x][pongBall.new_y] = true;                    //Draw new ball
  gamearea[pongBall.old_x][pongBall.old_y] = false;                   //Delete old ball
}

//function for the victory situation of one player
void winner(int Player){
  clearGamearea(2);
  switch(Player){
      case 1: gamearea[0][15] = true;  break;
      case 2: gamearea[15][15] = true;  break;
  }
  endOfGame = true;
}

//function to reset the scoreboard on top
void resetScoreboard(){
  for(int i =0; i<=15; i++){
    gamearea[i][0] = false;
  }
}

//control the bats by a potentiometer
void potiControl(int value ,int player){
  int top;        //top part of the bat
  int mid;        //mid part of the bat
  int bot;        //bottom part of the bat
  int column;
  if(player == 1){
    column=1;
  }else{
    column=14;
  }

  if(value >= 0 && value <= 110){
    top=13;
    mid=14;
    bot=15;
  }
  else if(value >= 111 && value <= 219){
    top=12;
    mid=13;
    bot=14;
  }
  else if(value >= 220 && value <= 328){
    top=11;
    mid=12;
    bot=13;
  }
  else if(value >= 329 && value <= 437){
    top=10;
    mid=11;
    bot=12;
  }
  else if(value >= 438 && value <= 546){
    top=9;
    mid=10;
    bot=11;
  }
  else if(value >= 547 && value <= 655){
    top=8;
    mid=9;
    bot=10;
  }
  else if(value >= 656 && value <= 764){
    top=7;
    mid=8;
    bot=9;
  }
  else if(value >= 765 && value <= 873){
    top=6;
    mid=7;
    bot=8;
  }
  else if(value >= 874 && value <= 982){
    top=5;
    mid=6;
    bot=7;
  }
  else if(value >= 983 && value <= 1091){
    top=4;
    mid=5;
    bot=6;
  }
  else if(value >= 1092 && value <= 1200){
    top=3;
    mid=4;
    bot=5;
  }


  clearColumn(column);
  if(player == 1){
    batPlay1.topPos = top;
    batPlay1.midPos = mid;
    batPlay1.botPos = bot;
  }else{
    batPlay2.topPos = top;
    batPlay2.midPos = mid;
    batPlay2.botPos = bot;
  }
  gamearea[column][top]=true;
  gamearea[column][mid]=true;
  gamearea[column][bot]=true;
}

//adds a point to the scoreboard and checks for a victory situation
void AddPointScoreboard(int Player){
  if(Player == 1){
    for(int i=0; i<7; i++){
      if(!(gamearea[i][0])){
         gamearea[i][0] = true;
         break;
      }
    }
    if(gamearea[6][0]){
      winner(1);
      }
    }else{
      for(int i=15; i>=9; i--){
          if(!(gamearea[i][0])){
            gamearea[i][0] = true;
            break;
           }
      }
      if(gamearea[9][0]){
      winner(2);
      }
    }
 }

//collison handler for the bats
void checkReactCollision(){
  if(pongBall.new_x+pongBall.speedx == batPlay1.column && pongBall.new_y+pongBall.speedy  == batPlay1.topPos){     //Player 1 Top
    pongBall.speedx = 1;
    pongBall.speedy = -1;
  }else if(pongBall.new_x+pongBall.speedx == batPlay1.column && pongBall.new_y+pongBall.speedy  == batPlay1.midPos){   //Player 1 Mid
    pongBall.speedx = 1;
    pongBall.speedy = (pongBall.speedy)*-1;
  }else if(pongBall.new_x+pongBall.speedx == batPlay1.column && pongBall.new_y+pongBall.speedy  == batPlay1.botPos){   //Player 1 Bottom
    pongBall.speedx = 1;
    pongBall.speedy = 1;
  }else if(pongBall.new_x+pongBall.speedx == batPlay2.column && pongBall.new_y+pongBall.speedy  == batPlay2.topPos){   //Player 2 Top
    pongBall.speedx = -1;
    pongBall.speedy = -1;
  }else if(pongBall.new_x+pongBall.speedx == batPlay2.column && pongBall.new_y+pongBall.speedy  == batPlay2.midPos){   //Player 2 Mid
    pongBall.speedx = -1;
    pongBall.speedy = (pongBall.speedy)*-1;
  }else if(pongBall.new_x+pongBall.speedx == batPlay2.column && pongBall.new_y+pongBall.speedy == batPlay2.botPos){   //Player 2 Bottom
    pongBall.speedx = -1;
    pongBall.speedy = 1;
  }
 }

//check for the dismiss of the ball with the bat
 void checkMakeAPoint(){
     if(pongBall.new_x == batPlay1.column && pongBall.new_y != batPlay1.topPos && pongBall.new_y != batPlay1.midPos && pongBall.new_y != batPlay1.botPos){
     clearGamearea(2);
     AddPointScoreboard(2);
     startAGame();
   }else if(pongBall.new_x == batPlay2.column && pongBall.new_y != batPlay2.topPos && pongBall.new_y != batPlay2.midPos && pongBall.new_y != batPlay2.botPos){
     clearGamearea(2);
     AddPointScoreboard(1);
     startAGame();
   }
 }

//transfer the playground array to the LED matrix
void gameAreaTransfer(boolean area[16][16]){

    //put game transfer code here

}

//loop function
void loop() {

  potVal1 = analogRead(potPinP1ay1);
  potVal2 = analogRead(potPinP1ay2);
  potiControl(potVal1, 1);
  potiControl(potVal2, 2);
  checkReactCollision();
  moveBall();
  checkMakeAPoint();
  gameAreaTransfer(gamearea);
  if(endOfGame){
    delay(10000);
    endOfGame = false;
    resetScoreboard();
  }
  delay(400);

}
