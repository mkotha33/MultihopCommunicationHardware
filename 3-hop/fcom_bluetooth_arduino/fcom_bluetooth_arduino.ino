#include<SoftwareSerial.h>
#include <mcp_can.h>
#include <SPI.h>

SoftwareSerial bt(2,3); 
const int SPI_CS_PIN = 9;
MCP_CAN CAN(SPI_CS_PIN);
unsigned char str[1000];
unsigned char ch;
int i=0,j;
int f1=0;
int p;
unsigned int x;

void setup() {
  bt.begin(9600); 
 Serial.begin(9600);
    //pinMode(lmPin, INPUT);
    while (CAN_OK != CAN.begin(CAN_500KBPS))
    { 
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(100);
    }
    Serial.println("CAN BUS Shield init ok!");
}

void send_func(unsigned char str[],int i){
    
     for(p=0;p<i;p++){
            Serial.write(str[p]);
           // x=str[p];
            //Serial.print(x);
     }
          
     CAN.sendMsgBuf(0x30,0,i , str);
     delay(1000);
     f1=1;
}

void loop(){
  
    if(bt.available())
    {
      ch = bt.read();
      str[i] = ch;
      i++;
      f1=0;
    }
    else{
        if(f1==0)
        {
           send_func(str,i);
           i=0;
        }
    }
}
