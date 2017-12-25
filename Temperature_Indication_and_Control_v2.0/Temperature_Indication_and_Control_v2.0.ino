#include <dht.h>
dht DHT;

#define DHT11_PIN 9
int buzz=10;
int mlp=11;
int mrp=12;


void setup()
{
  Serial.begin(115200);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(buzz,OUTPUT);
  pinMode(mlp,OUTPUT);
  pinMode(mrp,OUTPUT);
  
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");

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
  
  int temp=DHT.temperature;
  Serial.println(temp);
  Serial.print("C");
  delay(1000);
  
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  
  if(temp>15 && temp<25)
  {
    digitalWrite(5,HIGH);
  }
  
  if(temp>=25 && temp<30)
  {
    digitalWrite(6,HIGH);
    digitalWrite(mlp,HIGH);
    digitalWrite(mrp,LOW);
  }

  if(temp>=30 && temp<45)
  {
    digitalWrite(7,HIGH);
    digitalWrite(buzz,HIGH);
    digitalWrite(mlp,HIGH);
    digitalWrite(mrp,LOW);
  }
  else
  {
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    delay(500);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    delay(500);
    digitalWrite(buzz,HIGH);
    digitalWrite(mlp,HIGH);
    digitalWrite(mrp,LOW);
  }
}
