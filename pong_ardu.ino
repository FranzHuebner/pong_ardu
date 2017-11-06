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
bool gamearea[16][16]

void setup() {
  for(int horiz = 0, horiz <= 8, horiz++){      //horizontral iterrieren
      for(int vert =0, vert <= 8, vert++){
        gamearea[horiz][vert]= false;
      }

  }

}

void potiControl(int value){
  if(value <= 0 && value <= 93)
  else if(value <= 94 && value <= 186)
  else if(value <= 187 && value <= 279)
  else if(value <= 280 && value <= 372)
  else if(value <= 373 && value <= 465)
  else if(value <= 466 && value <= 558)
  else if(value <= 559 && value <= 651)
  else if(value <= 652 && value <= 744)
  else if(value <= 745 && value <= 837)
  else if(value <= 838 && value <= 930)
  else if(value <= 931 && value <= 1023)
}

void loop() {
  // put your main code here, to run repeatedly:

  potVal1 = analogRead(potPinP1ay1);
  potVal2 = analogRead(potPinP1ay2);




  }
