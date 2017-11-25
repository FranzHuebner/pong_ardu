/*
 *name: pong_ardu.ino
 *version: 1.0
 *description: Pong-game based on our max7221lib.h, played on 4x64 led matrix with 4 max7221-ic's daisychained
 *authors: Richard Walter, Franz Huebner
 *web:https://github.com/FranzHuebner/pong_ardu
*/

//include neccessary lib's for the game
#include "max7221lib.h"
#include "TimerOne.h"
#include "time.h"

//global vars
int potPinP1ay1 = A1;			//input potentiometer pin for player 1 
int potPinP1ay2 = A2;			//input potentiometer pin for player 2
int potVal1 = 0;				//store the potentiometer value of player 1
int potVal2 = 0;				//store the potentiometer value of player 2
boolean gamearea[16][16];		//array for the gamearea
boolean endOfGame = false;      //flag for the end of game state
boolean ballPeriod;				//timer boolean

//struct for the ball
struct ball               
{
	int speedx;
	int speedy;
	int old_x;
	int old_y;
	int new_x;
	int new_y;
}pongBall;

//struct for the bats of the two players
struct bat
{
	int column;
	int topPos;
	int midPos;
	int botPos;
}batPlay1, batPlay2;

//set the upper/lower edge
void setEdge(){
  for(int i=0; i<=15;i++){
    gamearea[i][1]=true;
    gamearea[i][15]=true;
  }
}

//function to clear the game-matrix
//usage: area = 1 for whole game-matrix
//usage: area = 2 for playground without edges and scoreboard
void clearGamearea(int area) {

  int a;
  switch (area) {
  
  case 1: a = 0;
  case 2: a = 1;
  
  }

  for (int i = 15; i >=0 ; i--) {
   
	  for (int j = 15; j >= a; j--) {
      
		  gamearea[i][j] = false;
    }
  }
}

//function which is called after every goal and the beginning 
void startAGame() {

	clearGamearea(2);			//clear field
				
	int r = (rand() %2)*2-1;    //random start speed x
	int s = (rand() %3)-1;		//random start speed y
	int g = (rand() % 13) + 2;  //random y postion

	pongBall.speedx = r;		//speed x
	pongBall.speedy = s;		//speed y

	pongBall.new_x = 8;			//init position (x)
	pongBall.new_y = g;			//init position (y)

	
	setEdge();					//init edges
  }

//setup function that runs first - arduino specific
void setup() {

	srand(time(NULL));						//init randomize()
  
	startup_matrix();						//call library to ensure matrix is working
	clearGamearea(1);						//clear whole game-matrix
	
	startAGame();							//set ball + speed and edges 
	
	batPlay1.column = 1;					//init bat of player one 
	batPlay2.column = 14;					//init bat of player two

	Timer1.initialize(200000);				//init the timer for the ball movement with a 0.2 second period
	Timer1.attachInterrupt(setBallPeriod);	//attach intterupt to unsync ball and bat movement -> smoother gameplay

}

//set ball period to true
void setBallPeriod(){

	ballPeriod=true;

}

// function to clear one collumn in the matrix
void clearColumn(int column) {
	
	for (int i = 2; i < 15; i++) {
	
		gamearea[column][i] = false;
	
	}
}

//collision detection for the edges 
void checkWallCollision(){

	//colision with top or bottom -> revert ball speed
	if ((pongBall.new_y+pongBall.speedy <= 1 ) || (pongBall.new_y + pongBall.speedy >= 15)){
		
		pongBall.speedy = (pongBall.speedy)*-1; 
  
	}

}

//function which moves the ball
void moveBall() {
 	
	pongBall.old_x = pongBall.new_x;						//set old x coordinates
	pongBall.old_y = pongBall.new_y;						//set old y coordinates
  
	checkReactCollision();									//check for collision with player bats
	checkWallCollision();									//check for collision with edges

	pongBall.new_x = pongBall.new_x + pongBall.speedx;		//set new x speed
	pongBall.new_y = pongBall.new_y + pongBall.speedy;		//set new y speed
	
	checkWallCollision();									//check for a second collision after ball is hit by bat and 1 pixel away from the edge		
	
	gamearea[pongBall.new_x][pongBall.new_y] = true;        //draw new ball
	gamearea[pongBall.old_x][pongBall.old_y] = false;       //delete old ball
 
}

//print winn on the side of the winning player
void printWinner(int player){

//put the word win into the array
switch (player) {
  case 1: 
    // W
    gamearea[0][0] = true;
    gamearea[1][0] = true;
    gamearea[2][0] = true;
    gamearea[3][0] = true;
    gamearea[4][0] = true;
    gamearea[5][0] = true;
    gamearea[6][0] = true;
    gamearea[7][0] = true;
    gamearea[7][1] = true;
    gamearea[7][2] = true;
    gamearea[6][2] = true;
    gamearea[5][2] = true;
    gamearea[4][2] = true;
    gamearea[3][2] = true;
    gamearea[7][3] = true;
    gamearea[6][0] = true;
    gamearea[7][4] = true;
    gamearea[6][4] = true;
    gamearea[5][4] = true;
    gamearea[4][4] = true;
    gamearea[3][4] = true;
    gamearea[2][4] = true;
    gamearea[1][4] = true;
    gamearea[0][4] = true;

    //I
    gamearea[0][7] = true;
    gamearea[1][7] = true;
    gamearea[3][7] = true;
    gamearea[4][7] = true;
    gamearea[5][7] = true;
    gamearea[6][7] = true;
    gamearea[7][7] = true;
    gamearea[0][8] = true;
    gamearea[1][8] = true;
    gamearea[3][8] = true;
    gamearea[4][8] = true;
    gamearea[5][8] = true;
    gamearea[6][8] = true;
    gamearea[7][8] = true;

    //N
    gamearea[0][11] = true;
    gamearea[1][11] = true;
    gamearea[2][11] = true;
    gamearea[3][11] = true;
    gamearea[4][11] = true;
    gamearea[5][11] = true;
    gamearea[6][11] = true;
    gamearea[7][11] = true;

    gamearea[0][12] = true;
    gamearea[0][13] = true;

    gamearea[1][13] = true;
    gamearea[2][13] = true;
    gamearea[3][13] = true;
    gamearea[4][13] = true;
    gamearea[5][13] = true;
    gamearea[6][13] = true;
    gamearea[7][13] = true;

    gamearea[7][14] = true;
    gamearea[7][15] = true;

    gamearea[6][15] = true;
    gamearea[5][15] = true;
    gamearea[4][15] = true;
    gamearea[3][15] = true;
    gamearea[2][15] = true;
    gamearea[1][15] = true;
    gamearea[0][15] = true;
    break;
  case 2:
    //W
    gamearea[15][15] = true;
    gamearea[14][15] = true;
    gamearea[13][15] = true;
    gamearea[12][15] = true;
    gamearea[11][15] = true;
    gamearea[10][15] = true;
    gamearea[9][15] = true;
    gamearea[8][15] = true;

    gamearea[8][14] = true;

    gamearea[12][13] = true;
    gamearea[11][13] = true;
    gamearea[10][13] = true;
    gamearea[9][13] = true;
    gamearea[8][13] = true;

    gamearea[8][12] = true;

    gamearea[15][11] = true;
    gamearea[14][11] = true;
    gamearea[13][11] = true;
    gamearea[12][11] = true;
    gamearea[11][11] = true;
    gamearea[10][11] = true;
    gamearea[9][11] = true;
    gamearea[8][11] = true;

    //I

    gamearea[15][7] = true;
    gamearea[14][7] = true;

    gamearea[15][8] = true;
    gamearea[14][8] = true;

    gamearea[12][7] = true;
    gamearea[11][7] = true;
    gamearea[10][7] = true;
    gamearea[9][7] = true;
    gamearea[8][7] = true;

    gamearea[12][8] = true;
    gamearea[11][8] = true;
    gamearea[10][8] = true;
    gamearea[9][8] = true;
    gamearea[8][8] = true;

    //N
    gamearea[15][4] = true;
    gamearea[14][4] = true;
    gamearea[13][4] = true;
    gamearea[12][4] = true;
    gamearea[11][4] = true;
    gamearea[10][4] = true;
    gamearea[9][4] = true;
    gamearea[8][4] = true;
    
    gamearea[15][2] = true;
    gamearea[14][2] = true;
    gamearea[13][2] = true;
    gamearea[12][2] = true;
    gamearea[11][2] = true;
    gamearea[10][2] = true;
    gamearea[9][2] = true;
    gamearea[8][2] = true;

    gamearea[15][0] = true;
    gamearea[14][0] = true;
    gamearea[13][0] = true;
    gamearea[12][0] = true;
    gamearea[11][0] = true;
    gamearea[10][0] = true;
    gamearea[9][0] = true;
    gamearea[8][0] = true;

    gamearea[8][1] = true;
    gamearea[15][3] = true;
    break;
  }
}

//function which is called after one player won a round
//usage: int 1 = player 1
//usage: int 2 = player 2
void winner(int Player) {

	clearGamearea(1);			//clear whole field
	printWinner(Player);		//print the word win
	endOfGame = true;			//set end of game stat

}

//function to reset the scoreboard on top of the field
void resetScoreboard() {

	for (int i = 0; i <= 15; i++) {
		
		gamearea[i][0] = false;	//reset points
	
	}

}

//control the bats by a potentiometer
//usage: int value = value which comes from analogRead
//usage: int player = 1 for player 1 // 2 for player 2
void potiControl(int value, int player) {

	int top;        //top part of the bat
	int mid;        //mid part of the bat
	int bot;        //bottom part of the bat
	int column;		//column where the bat is printed

	if (player == 1) {
		column = 1;
	}
	else {
		column = 14;
	}

	if (value >= 0 && value <= 93) {
		top = 12;
		mid = 13;
		bot = 14;
	}
	else if (value >93 && value <= 186) {
		top = 11;
		mid = 12;
		bot = 13;
	}
	else if (value > 186 && value <= 279) {
		top = 10;
		mid = 11;
		bot = 12;
	}
	else if (value > 279 && value <= 372) {
		top = 9;
		mid = 10;
		bot = 11;
	}
	else if (value > 372 && value <= 465) {
		top = 8;
		mid = 9;
		bot = 10;
	}
	else if (value > 465 && value <= 558) {
		top = 7;
		mid = 8;
		bot = 9;
	}
	else if (value > 558 && value <= 651) {
		top = 6;
		mid = 7;
		bot = 8;
	}
	else if (value > 651 && value <= 744) {
		top = 5;
		mid = 6;
		bot = 7;
	}
	else if (value > 744 && value <= 837) {
		top = 4;
		mid = 5;
		bot = 6;
	}
	else if (value > 837 && value <= 930) {
		top = 3;
		mid = 4;
		bot = 5;
	}
	else if (value > 930 && value <= 1023) {
		top = 2;
		mid = 3;
		bot = 4;
	}

	clearColumn(column);		//clear column

	if (player == 1) {
		batPlay1.topPos = top;
		batPlay1.midPos = mid;
		batPlay1.botPos = bot;
	}
	else {
		batPlay2.topPos = top;
		batPlay2.midPos = mid;
		batPlay2.botPos = bot;
	}

	//print new bat position
	gamearea[column][top] = true;
	gamearea[column][mid] = true;
	gamearea[column][bot] = true;
}

//adds a point to the scoreboard and checks for a victory situation
void AddPointScoreboard(int Player) {

	if (Player == 1) {

		for (int i = 0; i<7; i++) {
			
			if (!(gamearea[i][0])) {
				
				gamearea[i][0] = true;	//print 1 point for player 1
				break;
			
			}
		}

		if (gamearea[6][0]) {

			winner(1);					//when the game area on postion [6][0] == true then player 1 wins
		
		}
	}
	else {
		
		for (int i = 15; i >= 9; i--) {
			
			if (!(gamearea[i][0])) {
				
				gamearea[i][0] = true;	//print one point for player 2
				break;
			
			}
		}

		if (gamearea[9][0]) {

			winner(2);					//when the game area on postion [9][0] == true then player 2 wins
		
		}
	}
}

//collison detection for the bats
void checkReactCollision() {

  if (pongBall.new_x + pongBall.speedx == batPlay1.column && pongBall.new_y + pongBall.speedy == batPlay1.topPos) {			//player 1 top
	 
	  pongBall.speedx = 1;
	  pongBall.speedy = -1;

  }
	else if (pongBall.new_x + pongBall.speedx == batPlay1.column && pongBall.new_y + pongBall.speedy == batPlay1.midPos) {  //player 1 mid
		
		pongBall.speedx = 1;
		pongBall.speedy = (pongBall.speedy)*-1;
	
	}
	else if (pongBall.new_x + pongBall.speedx == batPlay1.column && pongBall.new_y + pongBall.speedy == batPlay1.botPos) {  //player 1 bottom
		
		pongBall.speedx = 1;
		pongBall.speedy = 1;
	
	}
	else if (pongBall.new_x + pongBall.speedx == batPlay2.column && pongBall.new_y + pongBall.speedy == batPlay2.topPos) {  //player 2 top
		
		pongBall.speedx = -1;
		pongBall.speedy = -1;
  
	}
	else if (pongBall.new_x + pongBall.speedx == batPlay2.column && pongBall.new_y + pongBall.speedy == batPlay2.midPos) {   //player 2 mid
		
		pongBall.speedx = -1;
		pongBall.speedy = (pongBall.speedy)*-1;
	
	}
	else if (pongBall.new_x + pongBall.speedx == batPlay2.column && pongBall.new_y + pongBall.speedy == batPlay2.botPos) {   //player 2 bottom
		
		pongBall.speedx = -1;
		pongBall.speedy = 1;
	
	}
}

//check the bat column for dismissing the ball with the bat and give a point to the opponent
void checkMakeAPoint() {

	if (pongBall.new_x == batPlay1.column && pongBall.new_y != batPlay1.topPos && pongBall.new_y != batPlay1.midPos && pongBall.new_y != batPlay1.botPos) {
		
		clearGamearea(2);			//clear only the game-area
		startAGame();				//start new round
		AddPointScoreboard(2);		//add point for player 2
		
	}
	else if (pongBall.new_x == batPlay2.column && pongBall.new_y != batPlay2.topPos && pongBall.new_y != batPlay2.midPos && pongBall.new_y != batPlay2.botPos) {
		
		clearGamearea(2);			//clear only the game-area
		startAGame();				//start new round
		AddPointScoreboard(1);		//add point for player 1
		
	}
}

//transfer the playground array to the LED-matrix
void gameAreaTransfer(boolean area[16][16]) {

	transfer_matrix(area); //library function to transfer the array

}

//loop function - arduino specific
void loop() {
	//get potentionmeter input
	potVal1 = analogRead(potPinP1ay1);
	potVal2 = analogRead(potPinP1ay2);
	
	//call function with the values
	potiControl(potVal1, 1);
	potiControl(potVal2, 2);
	
	//check ball period and move ball if it is true
	if(ballPeriod){
		moveBall();
		ballPeriod=false;
	}
	//check if someone scored a point
	checkMakeAPoint();
	//transfer the game-array to the matrix
	gameAreaTransfer(gamearea);
	
	//check if game is over
	if (endOfGame) {
		//delay the proccess so you can see the winner
		delay(10000);

		endOfGame = false;	//reset end-of-game-state
		resetScoreboard();	//reset points
		startAGame();		//start new game
	}
}
