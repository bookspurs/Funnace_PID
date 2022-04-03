Vlad Pinchuk, [03.04.2022 19:01]
#include <max6675.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <EncButton.h>
#include "Furnace.h"

#include <AccelStepper.h>
#include <GyverPID.h>

GyverPID PID (1.0 , 1, 0, 10000);

#define IN1 24
#define IN2 25
#define IN3 26
#define IN4 27

AccelStepper DRIVE (8, IN1, IN3, IN2, IN4);

// Количество шагов максимум 2960
// На один градус цельсия 2.96 шага

LiquidCrystal_I2C lcd(0x27,16,2); 

int thermoDO_1 = 2;  //он же SO
int thermoCS_1 = 3;
int thermoCLK_1 = 4;  //он же SCK

int thermoDO_2 = 5;  
int thermoCS_2 = 6;
int thermoCLK_2 = 7;

int thermoDO_3 = 8;  
int thermoCS_3 = 9;
int thermoCLK_3 = 10;

int Enc_Temp = 0; // Переменная для выставления температуры через энкодер

MAX6675 thermocouple_1(thermoCLK_1, thermoCS_1, thermoDO_1);
MAX6675 thermocouple_2(thermoCLK_2, thermoCS_2, thermoDO_2);
MAX6675 thermocouple_3(thermoCLK_3, thermoCS_3, thermoDO_3);

const int buttonPin = 11; // Пин кнопки

EncButton<EB_TICK, 2, 3, 4> enc;

bool var = true;

void setup()
{
lcd.init();

PID.setDirection (NORMAL); // Больше разность - больше управляемый сигнал
PID.setLimits(0,2960);    // Пределы управления

}

void loop() 
{
  PID.input = T1; // Входное значение для регулятора

  enc.tick();
  if(enc.click() and var!=false)
    var=false;
  else if(enc.click() and var!=true)
    var=true;
  
  if(var)
  {
    Serial.println("MONITORNG");
    messure(lcd, thermocouple_1, thermocouple_2, thermocouple_3);
  }
  else
  {
    // При переходе в режим обнуляем ПИД
    PID.setpoint = 0;

    Serial.println("SET TEMP");
    lcd.setCursor(0,0);
    lcd.print("SET TEMP:")
    lcd.setCursor(0,1);
    lcd.print(Enc_Temp);

    // Если кнопка была снова нажата
    if(enc.click(){
      var=false;               // Выходим из режима
      PID.setpoint = Enc_Temp; // Передаем выставленую температуру в ПИД
      }

  }

  lcd.clear(); 
  DRIVE.moveTo(PID.getResult);
}