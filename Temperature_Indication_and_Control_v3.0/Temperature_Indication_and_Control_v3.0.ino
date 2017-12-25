#include <SoftwareSerial.h>
#include <dht.h>
#include <LiquidCrystal.h>

#define DHT11_PIN 13
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
dht DHT;
SoftwareSerial mySerial(9, 10);
int LED1=6, LED2=7, LED3=8;
int buzz=A0;
int count=0;
int temp;

void setup()
{
  mySerial.begin(9600);  
  Serial.begin(9600);
  
  lcd.begin(16,2);
  lcd.setCursor(0,1);
  lcd.print("Hello User !!");
  delay(2000);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("WELCOME");
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("TEMPERATURE CONTROL");
  lcd.setCursor(4,1);
  lcd.print("WITH GSM");
  
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(buzz,OUTPUT);
  
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
  delay(100);
}


void loop()
{
  Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  
  switch (chk)
  {
    case DHTLIB_OK:  
        Serial.print("OK,\t"); 
        break;
    
    case DHTLIB_ERROR_CHECKSUM: 
        Serial.print("Checksum error,\t"); 
        break;
    
    case DHTLIB_ERROR_TIMEOUT: 
        Serial.print("Time out error,\t"); 
        break;
    
    case DHTLIB_ERROR_CONNECT:
        Serial.print("Connect error,\t");
        break;
    
    case DHTLIB_ERROR_ACK_L:
        Serial.print("Ack Low error,\t");
        break;
    
    case DHTLIB_ERROR_ACK_H:
        Serial.print("Ack High error,\t");
        break;
    
    default: 
        Serial.print("Unknown error,\t"); 
        break;
  }
  
  temp=DHT.temperature;
  Serial.println(temp);
  Serial.print("C");
  lcd.setCursor(4,0);
  lcd.print(temp);
  lcd.setCursor(5,1);
  lcd.print("C");
  delay(1000);
  
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  delay(1000);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  
  if(temp>15 && temp<25)
  {
    digitalWrite(5,HIGH);
    count=0;
  }
  
  if(temp>=25 && temp<29)
  {
    digitalWrite(6,HIGH);
    analogWrite(buzz,HIGH);
    count=0;
  }

  if(temp>=30 && temp<60)
  {
    digitalWrite(7,HIGH);
    analogWrite(buzz,HIGH);
    while(count==0)
    {
      SendMessage();
      count++;
    }
  }

  if (mySerial.available()>0)
    Serial.write(mySerial.read());
}


void SendMessage()
{
  temp=DHT.temperature;
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919013591305\"\r"); // Replace x with mobile number
  delay(1000);
  Serial.println("The temp is ");
  Serial.print(temp);
  Serial.print("C");
  mySerial.println("The temp is ");// The SMS text you want to send
  mySerial.print(temp);
  mySerial.print("C");
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

