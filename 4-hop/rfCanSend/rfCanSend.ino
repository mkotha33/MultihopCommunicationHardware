//simple Tx on pin D12
//Written By : Mohannad Rawashdeh
// 3:00pm , 13/6/2013
//http://www.genotronex.com/
//..................................

//#include<SoftwareSerial.h>
#include<VirtualWire.h>
char *controller;
#include <SPI.h>
#include "mcp_can.h"

//SoftwareSerial bt(2,3);  
const int SPI_CS_PIN = 9;
MCP_CAN CAN(SPI_CS_PIN);  
//sck=13  si=11 so=12 

void setup() {
  //bt.begin(9600); 
  Serial.begin(9600); 
  while (CAN_OK != CAN.begin(CAN_500KBPS))              // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(100);
    }
   Serial.println("CAN BUS Shield init ok!");
    pinMode(13,OUTPUT);
    vw_set_ptt_inverted(true); //
    vw_set_tx_pin(8);
    vw_setup(2200);
}
int i=0;
int j=0;

void loop() 
{

    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
      unsigned char len;
unsigned char buf[5000];

unsigned char ch;
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf        
      for(i=0;i<len;i++){
          Serial.write(buf[i]);        
      }

      //controller="1" ;
      vw_send((uint8_t *)buf, strlen(buf));
      vw_wait_tx(); // Wait until the whole message is gone
      digitalWrite(13,1);
      delay(2000);
      

     for(j=0;j<len;j++)
     {
           buf[j]='\0';
     }
      
    }
}


