#include <Wire.h>
#include "DHT.h"
DHT dht;
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");

  dht.setup(2); // data pin 2
   // initialize the LCD,
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.clear();
  lcd.setCursor (0, 0); //
  lcd.print("");
  lcd.setCursor (0, 1); //
  lcd.print("");
  lcd.setCursor (0, 1); //
  delay(1000);
  lcd.print("");
  delay(1000);
  lcd.setCursor (0, 1); //
  lcd.print("");
  delay(1000);
}
void loop() {
   delay(dht.getMinimumSamplingPeriod());
  float humidity = dht.getHumidity(); // ดึงค่าความชื้น
  float temperature = dht.getTemperature(); // ดึงค่าอุณหภูมิ
  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.println(dht.toFahrenheit(temperature), 1);
  delay(1000);
  lcd.setCursor (5, 1); //character zero, line 
  lcd.print(temperature); // print text
   lcd.setCursor (3, 1); //character zero, line 
  lcd.print("->"); // print text
  lcd.setCursor (11, 1); //character zero, line 
  lcd.print("C"); // print text
  lcd.setCursor (5, 2); //character , line 
  lcd.print("Humidity"); // print text
  lcd.setCursor (3, 2); //character zero, line 
  lcd.print("->"); // print text
  lcd.setCursor (5, 3); //character , line 
  lcd.print(humidity); // print text
  lcd.setCursor (3, 3); //character zero, line 
  lcd.print("->"); // print text
  lcd.setCursor (11, 3); //character zero, line 
  lcd.print("%RH"); // print text
  lcd.setCursor (5, 4); //character , line 
  lcd.print("Temperature");
  lcd.setCursor (3, 4); //character zero, line 
  lcd.print("->"); // print text
  
  delay(1000);

}
