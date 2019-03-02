#include <SoftwareSerial.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h> 
#include<math.h> 
SoftwareSerial BTserial(10, 11);

int p=7,q=17,n,t,flag,e[100],d[100],temp[100],j,m[100],len,en[100],i; 
char msg[100]; 

int prime(long int pr) 
{ 
int i; 
j=sqrt(pr); 
for(i=2;i<=j;i++) 
{ 
    if(pr%i==0) 
    return 0; 
} 
return 1; 
}
void ce() 
{ 
int k; 
k=0; 
for(i=2;i<t;i++) 
{ 
    if(t%i==0) 
    continue; 
    flag=prime(i); 
    if(flag==1&&i!=p&&i!=q) 
    { 
        e[k]=i; 
        flag=cd(e[k]); 
        if(flag>0) 
        { 
            d[k]=flag; 
            k++; 
        } 
        if(k==99) 
        break; 
    } 
} 
}

void encrypt() 
{ 
long int pt,ct,key=e[0],k,len; 

i=0; 
len=strlen(msg); 
while(i!=len)  
{ 
    pt=m[i]; 
    pt=pt-96; 
    k=1; 
    for(j=0;j<key;j++) 
    { 
        k=k*pt; 
        k=k%n; 
    } 
    temp[i]=k; 
    ct=k+96; 
    en[i]=ct;
    
     
    i++; 
} 
en[i]=-1; 

Serial.print("THE ENCRYPTED MESSAGE:");
for(i=0;en[i]!=-1;i++) 
   {
   BTserial.write((en[i]));
   Serial.print((char)en[i]);
   
  
   
   }
   Serial.print("\n");
   delay(100); 
} 



long int cd(long int x) 
{ 
long int k=1; 
while(1) 
{ 
    k=k+t; 
    if(k%x==0) 
    return(k/x); 
} 
}
void decrypt() 
{ 
  Serial.print("*");
long int pt,ct,key=d[0],k,j,r; 
i=0; 
for(r=0;r<len;r++) 
{ 
    ct=temp[i]; 
    k=1; 
    for(j=0;j<key;j++) 
    { 
        k=k*ct; 
        k=k%n; 
    } 
    pt=k+96; 
    m[i]=pt; 
    i++; 
} 
m[i]=-1; 
Serial.println("\nTHE DECRYPTED MESSAGE IS\n"); 
for(i=0;m[i]!=-1;i++) 
Serial.print((char)m[i]); 
}








void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTserial.begin(38400);

}

void loop() {


  if(Serial.available())
  {
    String str=Serial.readString();
    Serial.print(str);
    //delay(100);
    len=str.length();
    //Serial.print(len);
    for(i=0;i<len;i++)
    {
    msg[i]=str[i];
    }
    msg[i]=0;
    flag=prime(p); 
    //Serial.print(msg);
if(flag==0) 
{ 
    //printf("\nWRONG INPUT\n"); 
  Serial.println("WRONG OUTPUT");
    //getch(); 
    //exit(1); 
} 
//printf("\nENTER ANOTHER PRIME NUMBER\n"); 
//scanf("%d",&q); 
flag=prime(q); 
if(flag==0||p==q) 
{ 
   
  Serial.println("WRONG OUTPUT");
    //getch(); 
    //exit(1); 
} 
//printf("\nENTER MESSAGE\n"); 
//fflush(stdin); 
//scanf("%[^\n]s",msg);
//Serial.Write(msg); 
for(i=0;msg[i]!='\0';i++) 
m[i]=msg[i]; 
n=p*q; 
t=(p-1)*(q-1); 
ce(); 



    
    //Serial.print(msg);
    encrypt();
    //decrypt();
  }

}
