/*
 *name: pong_ardu.ino
 *version: 0.0.1
 *description: Pong gamed based on the max7221lib.h, played on 4x64 led matrix with 4 max7221-ic's daisychained
 *authors: Richard Walter, Franz Huebner
 *web:https://github.com/FranzHuebner/pong_ardu
*/

#include "max7221lib.h"

byte test[DEVICECOUNT]= {B11111,B1111,B1111,B1111};
byte test2[DEVICECOUNT] = { B11,B111111,B100111,B10111 };

void setup(){

boolean gunther[16][16];

for(int i=0;i<16;i++){

  for(int j=0;j<16;j++){
    gunther[i][j]= false;
  }

  gunther[0][0] = true;
  gunther[0][1] = true;
  gunther[15][15] = true;
  gunther[0][15] = true;
  gunther[13][5] = true;

}

startup_matrix();

set_reg_decodemode(false);
set_reg_displaytest(false);


//clearMatrix();

transfer_matrix(gunther);
set_reg_displaytest(false);

}

void loop() {

delay(1000);
}
