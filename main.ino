//#include <max6675.h>
#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <EncButton.h>
#include "Furnace.h"

LiquidCrystal_I2C lcd(0x27,20,4); 

int thermoDO_1 = 2;  //он же SO
int thermoCS_1 = 3;
int thermoCLK_1 = 4;  //он же SCK

int thermoDO_2 = 5;  
int thermoCS_2 = 6;
int thermoCLK_2 = 7;

int thermoDO_3 = 8;  
int thermoCS_3 = 9;
int thermoCLK_3 = 10;

MAX6675 thermocouple_1(thermoCLK_1, thermoCS_1, thermoDO_1);
MAX6675 thermocouple_2(thermoCLK_2, thermoCS_2, thermoDO_2);
MAX6675 thermocouple_3(thermoCLK_3, thermoCS_3, thermoDO_3);

const int buttonPin = 11; // Пин кнопки

EncButton<EB_TICK, 2, 3, 4> enc;

bool var = true;

void setup()
{
lcd.init();
}

void loop() 
{
  enc.tick();
  if(enc.click() and var!=false)
    var=false;
  else if(enc.click() and var!=true)
    var=true;
  
  if(var)
  {
    Serial.println("regim 1");
    messure(lcd, thermocouple_1, thermocouple_2, thermocouple_3);
  }
  else
  {
    Serial.println("regim 2");
  }
  delay(500);
  lcd.clear(); 
}
