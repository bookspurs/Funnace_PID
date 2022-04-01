#ifndef FURNACE_H
#define FURNACE_H
#include <Arduino.h>
#include <max6675.h>
#include <LiquidCrystal_I2C.h>
void messure(LiquidCrystal_I2C lcd, MAX6675 thermocouple_1, MAX6675 thermocouple_2, MAX6675 thermocouple_3);

#endif
