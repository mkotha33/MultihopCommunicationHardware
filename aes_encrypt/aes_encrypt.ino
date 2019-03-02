#include "AES.h"
#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11);
AES aes ;

byte key[] = 
{
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
} ;
byte plain[] =
{
  // 0xf3, 0x44, 0x81, 0xec, 0x3c, 0xc6, 0x27, 0xba, 0xcd, 0x5d, 0xc3, 0xfb, 0x08, 0xf2, 0x73, 0xe6
  0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xE0, 0x00, 0x01, 0x02, 0x03, 0x05, 0x08, 0x0a, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
} ;
byte my_iv[] = 
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
} ;
String str;
byte cipher [4*N_BLOCK] ;
byte check [4*N_BLOCK] ;
int f=0;
void loop () 
{
  int i=0;
  while(Serial.available())
  {
    str=Serial.readString();
    f=1;
   }
   if(f)
   {
  
  int j=0;
  for(j=0;j<str.length();j++)
  plain[j]=(byte)str[j];
  prekey_test () ;
  f=0;
  }
}
void setup ()
{
  Serial.begin (9600) ;
  BTserial.begin(38400);
  Serial.print ("testng mode") ;

  prekey_test () ;
  
//  otfly_test () ;
//  otfly_test256 () ;
}

void prekey (int bits, int blocks)
{
  byte iv [N_BLOCK] ;
  
  long t0 = micros () ;
  byte succ = aes.set_key (key, bits) ;
  long t1 = micros()-t0 ;
  Serial.print ("set_key ") ; Serial.print (bits) ; Serial.print (" ->") ; Serial.print ((int) succ) ;
  Serial.print (" took ") ; Serial.print (t1) ; Serial.println ("us") ;
  t0 = micros () ;
  if (blocks == 1)
    succ = aes.encrypt (plain, cipher) ;
  else
  {
    for (byte i = 0 ; i < 16 ; i++)
      iv[i] = my_iv[i] ;
    succ = aes.cbc_encrypt (plain, cipher, blocks, iv) ;
  }
  t1 = micros () - t0 ;
  Serial.print ("encrypt ") ; Serial.print ((int) succ) ;
  Serial.print (" took ") ; Serial.print (t1) ; Serial.println ("us") ;
  
  
   for (byte i = 0 ; i < blocks*N_BLOCK; i++)
    {
      byte val =plain[i];
      Serial.print (val>>4, HEX) ; Serial.print (val&15, HEX) ; Serial.print (" ") ;
    }
    Serial.println () ;
    for (byte i = 0 ; i < blocks*N_BLOCK; i++)
    {
      byte val =cipher[i];
      Serial.print (val>>4, HEX) ; Serial.print (val&15, HEX) ; Serial.print (" ") ;
      BTserial.write(cipher[i]);
      
    }
    Serial.println () ;
    for (byte i = 0 ; i < N_BLOCK; i++)
    {
      byte val =iv[i];
      Serial.print (val>>4, HEX) ; Serial.print (val&15, HEX) ; Serial.print (" ") ;
    }
    Serial.println () ;
  
}

void prekey_test ()
{
  prekey (128, 4) ;
}


