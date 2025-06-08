#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Library for I2C LCD

// Initialize 16x2 LCD with I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ACS712 Current Sensor
int sensitivity = 185; // for 5A version
int adcvalue = 0;
int offsetvoltage = 2500; // Calibration value
double Voltage = 0;
double ecurrent = 0;

void setup()
{
  lcd.init(); // initialize the LCD
  lcd.backlight(); // turn on the backlight

  lcd.setCursor(0, 0);
  lcd.print("Solar Monitor");
  delay(1500); // Optional: short startup message
}

void loop()
{
  // Read and display voltage
  int sensorValue = analogRead(A1);
  float voltage = (sensorValue * 5.0) / 1023.0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("V: ");
  lcd.print(voltage, 2);
  lcd.print("V");

  // Read and display current
  adcvalue = analogRead(A0);
  Voltage = (adcvalue * 5000.0) / 1023.0; // Convert to mV
  ecurrent = (Voltage - offsetvoltage) / sensitivity;

  lcd.setCursor(0, 1);
  lcd.print("I: ");
  lcd.print(ecurrent, 2);
  lcd.print("A");

  delay(1000);
}
