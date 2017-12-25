#include <I2Cdev.h>
#include <Wire.h>

int temp_add = 72;
int c,f;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
}

void loop()
{
  Wire.beginTransmission(temp_add);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(temp_add,1);
  while(Wire.available()==0);
  c = Wire.read();
  f = double(c*9.0/5.0 + 32);
  Serial.print(c);
  Serial.print("C,");
  Serial.print(f);
  Serial.println("F.");
  delay(1000);
}
