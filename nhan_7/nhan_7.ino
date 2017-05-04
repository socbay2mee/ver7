#include <EEPROM.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(4,5); // RX, TX

#define M0 7
#define M1 6
String addr_slave="";
int a=0;
int addr_0= 0;
int addr_1= 2;

int CHIEU_DAI=0;
long DEM=0;
int BAO_GAO=20;
long XUNG=0;
long so_set=0;
boolean START=false;

int latchPin = 10;
int clockPin = 12;  //chân SH_CP của 74HC595
int dataPin = 11;   //Chân DS của 74HC595

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
      //truyen_theo_dia_chi(0,"L01-DEM-" + str_dem);     
      EEPROM_UPDATE(addr_1, DEM);
    }
 } 
  
}
void PHAT_HIEN()
{
  DEM=DEM+1;
  START=true;
  Serial.println(DEM);   
  String str_dem= String(DEM);
  truyen_theo_dia_chi(0,"L01-DEM-" + str_dem);     
  
  //EEPROM_UPDATE(addr_1, DEM);

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
void sleep()
{
  digitalWrite(M0, 1);
  digitalWrite(M1, 1);
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
void set_dia_chi()
{
  sleep();
  char ADR[6] = {0XC0,0X00,0X02,0X1A,0X02,0XC4}; // IN DIA CHI 2, KENH 2 VAO LORA-- M0&M1=1
  for(int i=0;i<=6;i++)
  {
    mySerial.print(ADR[i]);
  }
  delay(1000);
  normal();
}
void truyen_theo_dia_chi(int dia_chi,String dulieu)
{ 
  char  addr_master[3]    = {0X00,0X01,0X01};
  char  addr_quang_bao[3] = {0X00,0X03,0X03};
    for(int i=0;i<=3;i++)
    {
        if(dia_chi == 0)
       {
        mySerial.print(addr_master[i]);
       }
       else if( dia_chi == 10)
       {
        mySerial.print(addr_quang_bao[i]);
       }   
  }
   mySerial.print(dulieu);
}
void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600); 
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT);
    pinMode(8, INPUT_PULLUP); 
    attachInterrupt(0, ENCODER, FALLING); //Ngắt cạnh xuống
    attachInterrupt(1, PHAT_HIEN,FALLING); //Ngắt cạnh LEN

    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(M1, OUTPUT);
    pinMode(M0, OUTPUT);
    set_dia_chi();
    mySerial.println(DEM);
    so_set= EEPROM_READ(addr_0);
    DEM= EEPROM_READ(addr_1);
}

void loop()
{  
  while(mySerial.available())
  {
    String data_from_master = mySerial.readString().substring(1); //This is your Integer value
    Serial.println(data_from_master);
    addr_slave= data_from_master.substring(0,7);
    int dai= data_from_master.length();
    if(addr_slave=="L01-SET")
      {
       
        String respond ="L01-SET";
        truyen_theo_dia_chi(0,respond);  
        truyen_theo_dia_chi(10,data_from_master);  
        for(int i=0; i<=dai; i++)
        {
          if (data_from_master[i]== '|')
            {
               String str_so_set  = data_from_master.substring(8,i);
               String bien_so  = data_from_master.substring(i+1);
               so_set =str_so_set.toInt();
               Serial.println(so_set); 
               Serial.println(bien_so);       
            }
        }
      }
     else if(addr_slave=="L01-CMD")
      {
        if (data_from_master.substring(8,11)== "ONN")
        {
           String respond ="L01-ONN";
           digitalWrite(LED_BUILTIN, HIGH);   
           truyen_theo_dia_chi(0,respond);   
        }
        else if (data_from_master.substring(8,11) =="OFF")
        {
           String respond ="L01-OFF";
           digitalWrite(LED_BUILTIN, LOW);   
           truyen_theo_dia_chi(0,respond);   
        }
                   
      }
   // delay(100);
  } 
  
}   
