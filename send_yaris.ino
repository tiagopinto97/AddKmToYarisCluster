// demo: CAN-BUS Shield, send data
// loovee@seeed.cc

#include <SPI.h>

#define CAN_2515
// #define CAN_2518FD

// Set SPI CS Pin according to your hardware

#if defined(SEEED_WIO_TERMINAL) && defined(CAN_2518FD)
// For Wio Terminal w/ MCP2518FD RPi Hat：
// Channel 0 SPI_CS Pin: BCM 8
// Channel 1 SPI_CS Pin: BCM 7
// Interupt Pin: BCM25
const int SPI_CS_PIN  = BCM8;
const int CAN_INT_PIN = BCM25;
#else

// For Arduino MCP2515 Hat:
// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;
const int CAN_INT_PIN = 2;
#endif


#ifdef CAN_2518FD
#include "mcp2518fd_can.h"
mcp2518fd CAN(SPI_CS_PIN); // Set CS pin
#endif

#ifdef CAN_2515
#include "mcp2515_can.h"
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#endif
#include "can_messages.h"

void setup() {
    while (CAN_OK != CAN.begin(CAN_500KBPS)) {}
}

int calculateRpm(int rpm) {
  return rpm / 200;
}

// Function to extract the high byte (EA)
byte getHighByte(unsigned int num) {
  return (byte)(num >> 8);  // Shift the bits to get the high byte
}

// Function to extract the low byte (60)
byte getLowByte(unsigned int num) {
  return (byte)(num & 0xFF);  // Mask the lower 8 bits to get the low byte
}


int count = 0;
void loop() {
    //26 * 150 - 900kmh
    //25 * 200 - 900kmh
  
    while (count < 22 ) {
       // Speed
      int speed = 5 * 100;
      int rpm = 8000;
      // I did sniff my car for the data, however there is a good starrting point bellow
      //https://github.com/iDoka/awesome-automotive-can-id?tab=readme-ov-file#toyota
      //https://github.com/P1kachu/talking-with-cars/blob/master/notes/toyota-yaris.md
       byte data1[8] = {0x00, 0x00, 0x00, 0x00, 0x04, getHighByte(speed),getLowByte(speed), 0x00};
       byte data2[8] = {0x00, 0x00, 0x00, 0xFF, 0x00, getHighByte(speed),getLowByte(speed), 0x00};
       
       sendCANMessage(data1);
       sendCANMessage(data2);
       count+=1;
    }
    delay(150);
    count = 0;
}

void sendCANMessage(byte data[8]) {
  byte sendResult = CAN.sendMsgBuf(0xB4, 0, 8, data);
  delay(20);    
}

// END FILE
