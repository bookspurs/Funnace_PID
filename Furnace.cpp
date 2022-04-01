#include "Furnace.h"

// (вход, установка, п, и, д, период в секундах, мин.выход, макс. выход)
// PID функция
int computePID(float input, float setpoint, float kp, float ki, float kd, float dt, int minOut, int maxOut) {
  float err = setpoint - input;
  static float integral = 0, prevErr = 0;
  integral = constrain(integral + (float)err * dt * ki, minOut, maxOut);
  float D = (err - prevErr) / dt;
  prevErr = err;
  return constrain(err * kp + integral + D * kd, minOut, maxOut);
}

void messure(LiquidCrystal_I2C lcd, MAX6675 thermocouple_1, MAX6675 thermocouple_2, MAX6675 thermocouple_3) 
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
  lcd.clear(); 
}
