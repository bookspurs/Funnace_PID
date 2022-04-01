#include <max6675.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
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


void setup()
{
lcd.init();   
DRIVE.setMaxSpeed(200.0);
DRIVE.setAcceleration(3.0);
DRIVE.setSpeed(1);

pid.setDirection (NORMAL);
}


void loop() 
{
int T1 = thermocouple_1.readCelsius();
int T2 = thermocouple_2.readCelsius();
int T3 = thermocouple_3.readCelsius();

  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("T1:");
  lcd.print(T1);
  lcd.print(char(223));

  lcd.setCursor(0,1);
  lcd.print("T2:");
  lcd.print(T2);
  lcd.print(char(223));

  lcd.print(" T3:");
  lcd.print(T3);
  lcd.print(char(223));

  delay(500);
  lcd.clear(); 
}
