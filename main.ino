#include <Wire.h> 
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
int piezoPin = 20;

MAX6675 thermocouple_1(thermoCLK_1, thermoCS_1, thermoDO_1);
MAX6675 thermocouple_2(thermoCLK_2, thermoCS_2, thermoDO_2);
MAX6675 thermocouple_3(thermoCLK_3, thermoCS_3, thermoDO_3);

const int buttonPin = 11; // Пин кнопки

EncButton<EB_TICK, 2, 3, 4> enc; //объявления энкодера с кнопкой

bool var = true; //true - режим мониторинга; false - режим выставления температуры

void setup()
{
lcd.init();

PID.setDirection (NORMAL); // Больше разность - больше управляемый сигнал
PID.setLimits(0,2960);    // Пределы управления

}

void loop() 
{
  PID.input = thermocouple_1.readCelsius(); // Входное значение для регулятора

  enc.tick(); // проверка состояния энкодера
  
  if(var)
  {
    Serial.println("MONITORNG");
    
    if(enc.click())  // Если кнопка была нажата
       var=false;

       tone(piezoPin, 1000, 200);
        // Выходим из режима

    messure(lcd, thermocouple_1, thermocouple_2, thermocouple_3);
  }
  else
  {
    // При переходе в режим обнуляем ПИД
    PID.setpoint = 0;
    
    Serial.println("SET TEMP");
    lcd.setCursor(0,0);
    lcd.print("SET TEMP:");
    lcd.setCursor(0,1);
    lcd.print(Enc_Temp);

    if(enc.left()==true) //если енкодер повернуть влево для уменьшении темературы 
      if(Enc_Temp==0) //если была достигнута нижняя граница, то делаем ничего(выводим)
        Serial.println(Enc_Temp);
      else //если нет, то уменьшанем температуру посредством обращения к переменной Enc_Temp
        Enc_Temp--; // Enc_Temp=Enc_Temp-1
    if(enc.right()==true) //если енкодер повернуть вправо для увеличении темературы 
      if(Enc_Temp==1000) //если была достигнута вверхняя граница, то делаем ничего(выводим)
        Serial.println(Enc_Temp);
      else //если нет, то увеличиваем температуру посредством обращения к переменной Enc_Temp
        Enc_Temp++; // Enc_Temp=Enc_Temp+1


    // Если кнопка была нажата
    if(enc.click())
    {
      tone(piezoPin, 2000, 200);
      var=true;               // Выходим из режима
      PID.setpoint = Enc_Temp; // Передаем выставленую температуру в ПИД
    }

  }
  
  lcd.clear(); 
  DRIVE.moveTo(PID.getResult);
}
