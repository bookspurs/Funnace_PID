



void messure () {
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