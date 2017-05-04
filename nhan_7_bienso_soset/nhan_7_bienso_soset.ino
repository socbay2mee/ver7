#include <EEPROM.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(4,5); // RX, TX

#define M0 6
#define M1 7
int addr_0= 0;
int addr_1= 2;
int g1;
int CHIEU_DAI=0;
long DEM=0;
int BAO_GAO=20;
long XUNG=0;
String data_nhan;
String so_set;
String bien_so;
boolean START=false;

int latchPin = 10;
//chân SH_CP của 74HC595
int clockPin = 12;
//Chân DS của 74HC595
int dataPin = 11;

//mảng có 10 số (từ 0-9) và 
const byte Seg[10] = {
  0b11000000,//0 - các thanh từ a-f sáng
  0b11111001,//1 - chỉ có 2 thanh b,c sáng
  0b10100100,//2
  0b10110000,//3
  0b10011001,//4
  0b10010010,//5
  0b10000010,//6
  0b11111000,//7
  0b10000000,//8
  0b10010000,//9
};

void ENCODER()
{
 if(START==true) // bắt đầu tính chiều dài
 {  
    if(digitalRead(8) == LOW)
      XUNG++;
    else
      XUNG--;
      
    CHIEU_DAI=XUNG*0.01;
    
    if(digitalRead(3) == LOW) // phát hiện cạnh xuống không cho tính chiều dài
    {
      XUNG=0;
      BAO_GAO=20;
      START=false ;  
      CHIEU_DAI=0;
    }
    if(CHIEU_DAI == BAO_GAO + 10 )  // chiều dài quá 1,5 bao => tính 2 bao
    {
      DEM=DEM+1;
      BAO_GAO=BAO_GAO+20;
      mySerial.println(DEM);
      EEPROM_UPDATE(addr_1, DEM);
      //EEPROM.update(addr_1, DEM);
    }
 } 
  
}
void PHAT_HIEN()
{
  DEM=DEM+1;
  START=true;
  mySerial.println(DEM);
  EEPROM_UPDATE(addr_1, DEM);
  //EEPROM.update(addr_1, DEM);
}
void HIENTHI_LED7DOAN(unsigned long Giatri, byte SoLed) {
  
  byte *array= new byte[SoLed];
  for (byte i = 0; i < SoLed; i++) {
    //Lấy các chữ số từ phải quá trái
    array[i] = (byte)(Giatri % 10UL);
    Giatri = (unsigned long)(Giatri /10UL);
  }
  digitalWrite(latchPin, LOW);
  for (int i = SoLed - 1; i >= 0; i--)
    shiftOut(dataPin, clockPin, MSBFIRST, Seg[array[i]]); 
  
  digitalWrite(latchPin, HIGH);
  free(array);
}


void normal()
{
  digitalWrite(M0, 0);
  digitalWrite(M1, 0);
}
void EEPROM_UPDATE(int ADDR, int VALUE)
{  
   EEPROM.update(ADDR,VALUE);
   delay(100);
   EEPROM.update(ADDR+1,VALUE>>8);
   delay(100);   
}
int EEPROM_READ(int ADDR)
{
   int VALUE =( EEPROM.read(ADDR+1)<<8);
   VALUE |= EEPROM.read(ADDR); 
   return VALUE;
}
void setup()
{
    Serial.begin(9600);
      mySerial.begin(9600); 
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT);
    pinMode(8, INPUT_PULLUP); 
    attachInterrupt(0, ENCODER, FALLING); //Ngắt cạnh xuống
    attachInterrupt(1, PHAT_HIEN, RISING); //Ngắt cạnh LEN

     
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

   pinMode(M1, OUTPUT);
  pinMode(M0, OUTPUT);
  normal();
  mySerial.println(DEM);
 so_set= EEPROM_READ(addr_0);
 DEM= EEPROM_READ(addr_1);
  //so_set = EEPROM.read(addr_0);
 // DEM = EEPROM.read(addr_1);

}

void loop()
{  
  while(mySerial.available()) {
   //so_set = mySerial.parseInt(); //This is your Integer value
    data_nhan= mySerial.readString();
    int aa= data_nhan.length();
    Serial.print(data_nhan);
    delay(1000);
    mySerial.println("OK da nhan duoc so set");
 if (data_nhan[0]=='A')
    {
      int i;
    String add=data_nhan.substring(1,3);
      if(add=="01")
      {
        for( i=0;i<=data_nhan.length();i++)
        {
          //char data= data_nhan[i];
          if(data_nhan[i]==',');
          {
            bien_so= data_nhan.substring(i,aa);
            so_set= data_nhan.substring(3,i);
            //bien_so= data_nhan.substring(i,aa)
            
          }
          
        }
        g1=so_set.toInt();
        Serial.println(g1);
        Serial.println(bien_so);
      
      }
     
    }
//   EEPROM_UPDATE(addr_0, so_set);
  }
  HIENTHI_LED7DOAN(g1, 3); 
// if(DEM ==so_set)
 //  {DEM=0;}
   if(digitalRead(3) == LOW)
    {
      XUNG=0;
      BAO_GAO=20;
      START=false ;  
      CHIEU_DAI=0;
    }

 
}   
