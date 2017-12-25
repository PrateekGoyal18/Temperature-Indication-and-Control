#include <SPI.h>
#include <LiquidCrystal.h>

int t=0;
int sensor=A1;  // sets as A1 as the temp sensor input
float temp;
float tempc;
float tempf;
int motor=A3;
int buzzer=A2;

LiquidCrystal lcd(3,4,5,6,7,8);

void setup()
{
  pinMode(9,OUTPUT);  // LED1
  pinMode(10,OUTPUT); // LED2
  pinMode(11,OUTPUT); // LED3
  pinMode(12,OUTPUT); // LED4
  pinMode(13,OUTPUT); // LED5. It depends on the no. of cases you want your system to have
  
  pinMode(motor,OUTPUT);
  pinMode(buzzer,OUTPUT);

  // LCD functions
  lcd.begin(16,2);
  lcd.setCursor(0,1);
  lcd.print("Hello User !!");
  delay(2000);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("WELCOME");
  
  pinMode(sensor,INPUT);
}

void loop()
{
  lcd.setCursor(0,0);
  temp=analogRead(sensor);
  
  tempc=(temp*5)/10;
  tempf=(temp*1.8)+32;
  
  if((tempc > 1.0) && (tempc < 30.0))
  {
    digitalWrite(9,LOW);
    delay(500);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
  }
  
  else if((tempc > 30.0) && (tempc < 40.0))
  {
    digitalWrite(9,LOW);
    delay(500);
    digitalWrite(10,LOW);
    digitalWrite(11,HIGH);
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
  }
  
  else if((tempc > 40.0) && (tempc < 50.0))
  {
    digitalWrite(9,LOW);
    delay(500);
    digitalWrite(10,LOW);
    delay(500);
    digitalWrite(11,LOW);
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
  }    
  
  else if((tempc > 50.0) && (tempc < 60.0))
  {
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
      digitalWrite(12,LOW);
      digitalWrite(13,HIGH);
  }
  
  else if((tempc > 60.0) && (tempc < 70.0))
  {
    digitalWrite(motor,LOW);
    digitalWrite(buzz,HIGH);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
  }
  
  else
  {
    digitalWrite(motor,HIGH);
    digitalWrite(buzz,LOW);
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
 }
 
  lcd.print("Temp. in C = "); // prints the temperature in degree C
  lcd.println(tempc);
  lcd.setCursor(0,1);
  lcd.print("Temp. in F = "); // prints the temperature in degree F
  lcd.println(tempf);
}
