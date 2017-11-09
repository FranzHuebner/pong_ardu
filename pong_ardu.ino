/*
 *name: pong_ardu.ino
 *version: 0.0.1
 *description: Pong gamed based on the max7221lib.h, played on 4x64 led matrix with 4 max7221-ic's daisychained
 *authors: Richard Walter, Franz Huebner
 *web:
*/

#include "max7221lib.h"

byte tett[4]= {B0,B0,B0,B1};

void setup() {

SPI.begin();
startSetup();
// put your setup code here, to run once:
set_reg_shutdownmode(false);

}

void loop() {
write_SPI_ALL(OPCODE_DIGIT0,tett);
set_reg_displaytest(false);
delay(1000);
}
