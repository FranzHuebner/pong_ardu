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

void loop() {
  // put your main code here, to run repeatedly:

  potVal1 = analogRead(potPinP1ay1);
  potVal2 = analogRead(potPinP1ay2);




  }
}
