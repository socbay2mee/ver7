#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3); // RX, TX

#define M0 4
#define M1 5

String  data_software = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String  dia_chi_slave="";

void setup()  
{
  Serial.begin(9600);
  mySerial.begin(9600); 
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  set_dia_chi();
}
void set_dia_chi()
{
  sleep();  
  char ADR[6] = {0XC0,0X00,0X01,0X1A,0X01,0XC4}; // IN DIA CHI 1, KENH 1 VAO LORA-- M0&M1=1
  for(int i=0;i<=6;i++)
  {
     mySerial.print(ADR[i]);
  }
  delay(1000);  
  normal();
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
void truyen_theo_dia_chi(int dia_chi,String dulieu)
{
  char  addr_chuyen_1[3] = {0X00,0X02,0X02};
  char  addr_chuyen_2[3] = {0X00,0X03,0X03};
  for(int i=0;i<=3;i++)
  {
    if(dia_chi == 1)
    {
      mySerial.print(addr_chuyen_1[i]);
    }
    else if( dia_chi == 2)
    {
      mySerial.print(addr_chuyen_2[i]);
    }   
  }
  mySerial.println(dulieu);
}
void loop() 
{
  while (mySerial.available())  // nhận số đếm và phản hồi từ lora hiển thị C#
  { 
      String data_from_lora_slave = mySerial.readString().substring(1);
      String respond_slave= data_from_lora_slave.substring(0,7);
      
      if (respond_slave =="L01-ONN")
      {
        digitalWrite(LED_BUILTIN, HIGH);   
      }
      else if (respond_slave =="L01-OFF")
      {
        digitalWrite(LED_BUILTIN, LOW); 
      }
       
      Serial.println(data_from_lora_slave);    
  }      
     
  while (Serial.available())    // gửi số từ C# qua lora
  {    
     char data = (char)Serial.read(); 
     data_software += data;
     if (data == '\n')
     {
        stringComplete = true;
     } 
  }
  if (stringComplete) 
  {
     dia_chi_slave= data_software.substring(0,3);
     if(dia_chi_slave=="L01")
     {
        truyen_theo_dia_chi(1,data_software);                
        data_software= "";
        stringComplete = false;
     }
     if(dia_chi_slave=="L02")
     {
        truyen_theo_dia_chi(2,data_software);                
        data_software= "";
        stringComplete = false;
     }
     else
     {
        data_software = "";
        stringComplete = false;
     }
  }
  
}     
  


