#include<SoftwareSerial.h>
#include <SPI.h>
#include "mcp_can.h"

SoftwareSerial bt(2,3);  
const int SPI_CS_PIN = 9;
MCP_CAN CAN(SPI_CS_PIN);  
//sck=13  si=11 so=12 

void setup() {
  bt.begin(9600); 
  Serial.begin(9600); 
  while (CAN_OK != CAN.begin(CAN_500KBPS))              // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(100);
    }
   Serial.println("CAN BUS Shield init ok!");
}
int i1=0;
int j1=0;
unsigned char ch;

   
void loop() 
{

    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
      //Serial.println("available");
      unsigned char len;
unsigned char buf[5000];


        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf        
      for(i1=0;i1<len;i1++){
          
         //decrypt
         if(i1%2==0){
          buf[i1] = buf[i1] - (unsigned char)1;
         }
         else{
          buf[i1] = buf[i1] + (unsigned char)1;
         }
         Serial.write(buf[i1]); 
          ch = buf[i1];
          //ch=decrypt(ch);
          
         bt.write(ch);
         
        }
        bt.write('\n');
        //Serial.print("\n"); 
       //bt.write(10);
        //bt.write(13);
        for(j1=0;j1<len;j1++)
        {
           buf[j1]='\0';
        }
       
      }
      
}


