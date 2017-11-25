/*
*name: max7221lib.h
*version: 1.0
*description: led SPI library to control 4 daisychained max7221
*authors: Franz Hübner, Richard Walter
*web:https://github.com/FranzHuebner/pong_ardu
*/


//includeguard
#pragma once

//Arduino-SPI
#include <SPI.h>

//include arduino for version > 1.0
#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

//number of casceded devices
#define DEVICECOUNT 4

//define the opcodes for the registers
//on the max 7221 --> see datasheet for registers
//web: https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf
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
#define OPCODE_SHUTDOWN    B1100    //12
#define OPCODE_DISPLAYTEST B1111    //15

//define ports
#define SPI_CS  10                  //slave-select
#define SPI_MOSI 11                 //dataIN
#define SPI_CLK 13                  //clock

//define matrix
#define MATRIX_X 16
#define MATRIX_Y 16

//arrays for our startfunction to use shiftout
byte matrixdata[16];
byte status[64];

//settings for SPI -> see datasheet of Max7221
SPISettings max_Settings(10000000,MSBFIRST,SPI_MODE0);

//send data to one matrix,everything else will be no-op'ed out
void SPI_transfer(int address, byte opcode, byte data){

 //enable transaction
  SPI.beginTransaction(max_Settings);

  //ss to low to send data
  digitalWrite(SPI_CS,LOW);

  //send our data
  SPI.transfer(opcode);
  SPI.transfer(data);

  //opcodes to add if data is not on the first device
  if(address > 1){
    for(int i=1;i<=address;i++){
      SPI.transfer(OPCODE_NOOP);
	  SPI.transfer(OPCODE_NOOP);
	}
  }
  //end transaction
  SPI.endTransaction();

  //see SPI definition
  digitalWrite(SPI_CS,HIGH);

}

//write the same opcode(register) and an byte array to the matrix
void write_SPI_ALL(volatile byte opcode, volatile byte data[DEVICECOUNT]){

	//see SPI standard
	digitalWrite(SPI_CS, LOW);

	//init transaction
	SPI.beginTransaction(max_Settings);

	//transfer our bundle via SPI
	for (int i = 0; i < DEVICECOUNT; i++){
		SPI.transfer(opcode);
		SPI.transfer(data[i]);
	}

	//end transaction
	SPI.endTransaction();

	//see SPI standard
	digitalWrite(SPI_CS, HIGH);	
}

//set set true to decode      format: 11111111
// set false for no decoding  format: 00000000
void set_reg_decodemode(boolean b){

byte c[DEVICECOUNT];

//check set
if(b){

  for(int f=0;f<DEVICECOUNT;f++){
    c[f]= B11111111; //true
  }

  write_SPI_ALL(OPCODE_DECODEMODE,c); // true

}else{

  for(int f=0;f<DEVICECOUNT;f++){
    c[f]= B0; //false
  }

write_SPI_ALL(OPCODE_DECODEMODE,c); //false
}
}

//set true for SHUTDOWN           format: XXXXXXX0
//set false for normal operation  format: XXXXXXX1
void set_reg_shutdownmode(boolean b){

byte c[DEVICECOUNT];

if(b){

  for(int f=0;f<DEVICECOUNT;f++){
    c[f]= B0;
  }

write_SPI_ALL(OPCODE_SHUTDOWN,c); // true

}else{

  for(int f=0;f<DEVICECOUNT;f++){
    c[f]= B11111111;  //false
  }

write_SPI_ALL(OPCODE_SHUTDOWN,c); //false
}
}

//set value from 0 to 15
void set_reg_intensity(int inp){

//errorhandling
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

//errorhandling
if((input<0) || (input >7)){
  return;
}

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

byte c[DEVICECOUNT];

if(b){

  for(int f=0;f<DEVICECOUNT;f++){
    c[f]= B11111111;
  }

write_SPI_ALL(OPCODE_DISPLAYTEST,c); // true

}else{

  for(int f=0;f<DEVICECOUNT;f++){
    c[f]= B0;  //false
  }

write_SPI_ALL(OPCODE_DISPLAYTEST,c); //false
}
}

//fake SPI - required after the reset of the matrix
//normal SPI isn´t working so we just form an array and transfer it via shiftout
//after resetting all registers it´s possible to use normal SPI
void start_spi(int matrixnumber, volatile byte opcode, volatile byte data) {
	
	//create our neccessary variables
	int offset = matrixnumber * 2;
	int maxcountbytes = DEVICECOUNT * 2;

	//fill our array with null
	for (int i = 0; i < maxcountbytes; i++) {
		matrixdata[i] = B0;
	}
		
	//put our device data into the array
	matrixdata[offset + 1] = opcode;
	matrixdata[offset] = data;

	digitalWrite(SPI_CS, LOW);
	
	//shiftout our data
	for (int i = maxcountbytes; i > 0; i--) {
		shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, matrixdata[i - 1]);
	}

	digitalWrite(SPI_CS, HIGH);
}

//startup the matrix to gain full usability via start_spi
//not neccessary after just resetting the arduino
//needed after full power loss of the matrix
void startup_matrix() {

	//set our pins to use everthing -> n. as SPI.begin();
	pinMode(SPI_MOSI, OUTPUT);
	pinMode(SPI_CLK, OUTPUT);
	pinMode(SPI_CS, OUTPUT);
	digitalWrite(SPI_CS, HIGH);

	//iterate through all 4 devices
	for (int i = 0; i<DEVICECOUNT; i++) {

		//set our initial values through shiftout
		start_spi(i, OPCODE_DISPLAYTEST, 0); //no displaytest
		start_spi(i, OPCODE_SCANLIMIT, B111);//scanlimit to max (7)
		start_spi(i, OPCODE_DECODEMODE, 0);  //no deodemode
				
		//set the offset
		int offset = i * 8;
		
		//iterate through the field and set our array to shift it out 
		for (int g = 0; g<8; g++) {
			status[offset + g] = 0;
			start_spi(i, g + 1, status[offset + g]);
		}

		//set shutdown-mode to false for normal operation
		start_spi(i, OPCODE_SHUTDOWN, 255);

	}

	//set the last parameters
	set_reg_scanlimit(1);
	set_reg_intensity(7);

}

//clear all LEDS on the connected matrix
void clearMatrix(){

  //byte array with zeros
  byte cclear[DEVICECOUNT];

  //fill array with b zero -> size = DEVICECOUNT
  for(int f=0;f<DEVICECOUNT;f++){
    cclear[f]= B0;
  }

  write_SPI_ALL(OPCODE_DIGIT0,cclear);
  write_SPI_ALL(OPCODE_DIGIT1,cclear);
  write_SPI_ALL(OPCODE_DIGIT2,cclear);
  write_SPI_ALL(OPCODE_DIGIT3,cclear);
  write_SPI_ALL(OPCODE_DIGIT4,cclear);
  write_SPI_ALL(OPCODE_DIGIT5,cclear);
  write_SPI_ALL(OPCODE_DIGIT6,cclear);
  write_SPI_ALL(OPCODE_DIGIT7,cclear);

}

//function to transfer the whole field
void transfer_matrix(boolean inputMatrix[MATRIX_X][MATRIX_Y]){

	//init opcode array
	byte opcode_array[8] = {
		B1000,
		B111,
		B110,
		B101,
		B100,
		B11,
		B10,
		B1
	};

	//init bytes to send
	byte darray[4] = {
		B0,
		B0,
		B0,
		B0
	};

	boolean c;

	//outer loop
	for (int outer = 0; outer < 8; outer++) {

		int bb = 0;
		int aa = 0;
		int kk = 0;
		int ll = 0;

		//loop 1
		for (int i = 0; i < 8; i++) {

			//inner loop 1 for byte 3
			c = inputMatrix[outer][i];

			if (c) {
				bitSet(darray[3], bb);
			}
			else {
				bitClear(darray[3], bb);
			}
			bb++;
		}

		//inner loop 2 for b2
		for (int o = 8; o < 16; o++) {
			c = inputMatrix[outer][o];
			if (c) {
				bitSet(darray[2], aa);
			}
			else {
				bitClear(darray[2], aa);
			}
			aa++;
		}

		//inner loop 3 for b0
		for (int d = 8; d < 16; d++) {

			c = inputMatrix[outer + 8][d];
			if (c) {
				bitSet(darray[0], kk);
			}
			else {
				bitClear(darray[0], kk);
			}
			kk++;
		}

		//inner loop 4 for b1
		for (int q = 0; q < 8; q++) {

			c = inputMatrix[outer + 8][q];

			if (c) {

				bitSet(darray[1], ll);

			}
			else {

				bitClear(darray[1], ll);

			}

			ll++;
		}

		write_SPI_ALL(opcode_array[outer], darray);

	}


  }
