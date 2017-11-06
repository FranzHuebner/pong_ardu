/*
*name: max7221lib.h
*version: 0.0.1
*description: led SPI library to control 4 daisychained max7221 and write an array to the board
*authors: Franz Hübner, Richard Walter
*web:
*/


//includeguard
#ifndef max7221lib_h
#define max7221lib_h

#include <SPI.h>
#include "LedControl.h"

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

//Define the opcodes for the registers
//on the max 7221 --> see datasheet for registers

//numer of casceded devices
#define DEVICECOUNT 4

#define OPCODE_NOOP   0        //0x00
#define OPCODE_DIGIT0 1        //0x01
#define OPCODE_DIGIT1 2        //0x02
#define OPCODE_DIGIT2 3        //0x03
#define OPCODE_DIGIT3 4        //0x04
#define OPCODE_DIGIT4 5        //0x05
#define OPCODE_DIGIT5 6        //0x06
#define OPCODE_DIGIT6 7        //0x07
#define OPCODE_DIGIT7 8        //0x08
#define OPCODE_DECODEMODE  9   //0x09
#define OPCODE_INTENSITY   10  //0x0a
#define OPCODE_SCANLIMIT   11  //0x0b
#define OPCODE_shutDown    12  //0x0c
#define OPCODE_DISPLAYTEST 15  //0x0f

//Define Ports
#define SPI_CS  10 //Slave select
#define SPI_MOSI 11 // DataIN
#define SPI_CLK 13 //clock

//data s
//2*4 data
byte fullData[8];

//always set cs to out or arduino will interact as slave
pinMode(SPI_CS,OUTPUT);

//settings for SPI
SPISettings max_Settings(8000000,MSBFIRST,SPI_MODE0);

//send to one matrix else will be nooped out
void SPI_transfer(int address, int opcode, byte data){

  byte b_opcode = byte(opcode),
 //enable transaction
  SPI.beginTransaction(max_Settings);
  //ss to low to send data
  digitalWrite(SPI_CS,LOW);

  if(address > 1){
    for(i=1;i<=address;i++){
      SPI.transfer(byte(OPCODE_NOOP));
      SPI.transfer(byte(OPCODE_NOOP));
    }
  }

  SPI.transfer(b_opcode);
  SPI.transfer(data);

  digitalWrite(SPI_CS,HIGH);
  SPI.endTransaction();

}

//write the same opcode + byte array to chain
void write_SPI_ALL(int opcode,byte[4] data){

  //transfer int to byte
  byte b_opcode = byte(opcode),
  //enable transaction
  SPI.beginTransaction(max_Settings);
  //set cs to low
  digitalWrite(SPI_CS,LOW);

  //loop the chain
  for(c=0;c<=DEVICECOUNT;c++){
    spi.transfer(b_opcode);
    spi.transfer(data[c]);
  }

//reset SPI_CS
digitalWrite(SPI_CS,HIGH);

SPI.endTransaction();

}

//set whole reg
void set_reg_decodemode(boolean b){

}

#endif	//max7221lib.h
