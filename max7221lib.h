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

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

//Define the opcodes for the registers
//on the max 7221 --> see datasheet for registers

//numer of casceded devices
#define DEVICECOUNT 4

#define OPCODE_NOOP   B0            //0
#define OPCODE_DIGIT0 B1            //1
#define OPCODE_DIGIT1 B10           //2
#define OPCODE_DIGIT2 B11           //3
#define OPCODE_DIGIT3 B100          //4
#define OPCODE_DIGIT4 B101          //5
#define OPCODE_DIGIT5 B110          //6
#define OPCODE_DIGIT6 B111          //7
#define OPCODE_DIGIT7 B1000         //8
#define OPCODE_DECODEMODE  B1001    //9
#define OPCODE_INTENSITY   B1010    //10
#define OPCODE_SCANLIMIT   B1011    //11
#define OPCODE_shutDown    B1100    //12
#define OPCODE_DISPLAYTEST B1111    //15

//Define Ports
#define SPI_CS  10                  //Slave select
#define SPI_MOSI 11                 // DataIN
#define SPI_CLK 13                  //clock

//settings for SPI
SPISettings max_Settings(8000000,MSBFIRST,SPI_MODE0);

//send to one matrix else will be nooped out
void SPI_transfer(int address, byte opcode, byte data){

 //enable transaction
  SPI.beginTransaction(max_Settings);
  //ss to low to send data
  digitalWrite(SPI_CS,LOW);

  SPI.transfer(opcode);
  SPI.transfer(data);

  if(address > 1){
    for(int i=1;i<=address;i++){
      SPI.transfer(OPCODE_NOOP);
      SPI.transfer(OPCODE_NOOP);
    }
  }

  digitalWrite(SPI_CS,HIGH);
  SPI.endTransaction();

}

//write the same opcode + byte array to chain
void write_SPI_ALL(byte opcode,byte data[DEVICECOUNT]){

  //enable transaction
  SPI.beginTransaction(max_Settings);
  //set cs to low
  digitalWrite(SPI_CS,LOW);

  //loop the chain
  for(int c=0;c<=DEVICECOUNT;c++){
    SPI.transfer(opcode);
    SPI.transfer(data[c]);
  }

//reset SPI_CS
digitalWrite(SPI_CS,HIGH);

//END transaction
SPI.endTransaction();

}


//set set true to decode      format: 11111111
// set false for no decoding  format: 00000000
void set_reg_decodemode(boolean b){

//check set
if(b){

  byte c[DEVICECOUNT];

  for(int f=0;f<DEVICECOUNT;f++){
    c[f]= B11111111; //true
  }

//opcode -- data
write_SPI_ALL(OPCODE_DECODEMODE,c); // true
}else{

  byte d[DEVICECOUNT];

  for(int f=0;f<DEVICECOUNT;f++){
    d[f]= B0; //false
  }

write_SPI_ALL(OPCODE_DECODEMODE,d); //false
}

}

//set true for shutdown           format: XXXXXXX0
//set false for normal operation  format: XXXXXXX1
void set_reg_shutdownmode(boolean b){

if(b){

  byte c[DEVICECOUNT];

  for(int f=0;f<DEVICECOUNT;f++){
    c[f]= B0;
  }

write_SPI_ALL(OPCODE_shutDown,c); // true

}else{
//byte sparen durch only c
  byte d[DEVICECOUNT];

  for(int f=0;f<DEVICECOUNT;f++){
    d[f]= B11111111;  //false
  }

write_SPI_ALL(OPCODE_shutDown,d); //false
}
}

//set value from 0 to 15
void set_reg_intensity(int inp){

//error handling
if ((inp<0)||(inp>15)){
  return;
}

byte c[DEVICECOUNT];

switch (inp){
  case 0:
  for(int f=0;f<DEVICECOUNT;f++){
      c[f]= B0  ;
    }
    break;

  case 1:
  for(int f=0;f<DEVICECOUNT;f++){
      c[f]= B1  ;
    }
    break;

    case 2:
    for(int f=0;f<DEVICECOUNT;f++){
        c[f]= B10;
      }
      break;

  case 3:
  for(int f=0;f<DEVICECOUNT;f++){
          c[f]= B11;
  }
  break;

  case 4:
  for(int f=0;f<DEVICECOUNT;f++){
          c[f]= B100;
  }
  break;
//s
  case 5:
  for(int f=0;f<DEVICECOUNT;f++){
          c[f]= B101;
  }
  break;

  case 6:
  for(int f=0;f<DEVICECOUNT;f++){
          c[f]= B110;
  }
  break;

  case 7:
  for(int f=0;f<DEVICECOUNT;f++){
          c[f]= B111;
  }
  break;

  case 8:
  for(int f=0;f<DEVICECOUNT;f++){
          c[f]= B1000;
  }
  break;

  case 9:
  for(int f=0;f<DEVICECOUNT;f++){
          c[f]= B1001;
  }
  break;

  case 10:
  for(int f=0;f<DEVICECOUNT;f++){
          c[f]= B1010;
  }
  break;

  case 11:
  for(int f=0;f<DEVICECOUNT;f++){
          c[f]= B1011;
  }
  break;

  case 12:
  for(int f=0;f<DEVICECOUNT;f++){
          c[f]= B1100;
  }
  break;

  case 13:
  for(int f=0;f<DEVICECOUNT;f++){
          c[f]= B1101;
  }
  break;

  case 14:
  for(int f=0;f<DEVICECOUNT;f++){
          c[f]= B1110;
  }
  break;

  case 15:
  for(int f=0;f<DEVICECOUNT;f++){
          c[f]= B1111;
  }
  break;
}

write_SPI_ALL(OPCODE_INTENSITY,c);

}

//scanlimit

//set for min scanlimit      format: XXXXX000
//set max scanlimit          format: XXXXX111

void set_reg_scanlimit(int input){

byte c[DEVICECOUNT];

switch (input){
  case 0:
  for(int f=0;f<DEVICECOUNT;f++){
      c[f]= B0;
    }
    break;

    case 1:
    for(int f=0;f<DEVICECOUNT;f++){
        c[f]= B1;
      }
      break;

      case 2:
      for(int f=0;f<DEVICECOUNT;f++){
          c[f]= B10;
        }
        break;

      case 3:
      for(int f=0;f<DEVICECOUNT;f++){
          c[f]= B11;
      }
        break;

      case 4:
      for(int f=0;f<DEVICECOUNT;f++){
          c[f]= B100;
      }
        break;

        case 5:
        for(int f=0;f<DEVICECOUNT;f++){
            c[f]= B101;
          }
          break;

          case 6:
          for(int f=0;f<DEVICECOUNT;f++){
              c[f]= B110;
            }
            break;

          case 7:
          for(int f=0;f<DEVICECOUNT;f++){
              c[f]= B111;
          }
          break;

write_SPI_ALL(OPCODE_SCANLIMIT,c);

}

}

//displaytest
//set true for displaytest           format: XXXXXXX1
//set false for normal operation     format: XXXXXXX0
void set_reg_displaytest(boolean b){

if(b){

  byte c[DEVICECOUNT];

  for(int f=0;f<DEVICECOUNT;f++){
    c[f]= B11111111;
  }

write_SPI_ALL(OPCODE_DISPLAYTEST,c); // true

}else{

  byte d[DEVICECOUNT];

  for(int f=0;f<DEVICECOUNT;f++){
    d[f]= B0;  //false
  }

write_SPI_ALL(OPCODE_DISPLAYTEST,d); //false
}
}

//startup
void startSetup(){

//always set cs to out or arduino will interact as slave
pinMode(SPI_CS,OUTPUT);

set_reg_decodemode(false);
set_reg_displaytest(false);
set_reg_scanlimit(7);
set_reg_intensity(10);

}


#endif	//max7221lib.h
