#include <LiquidCrystal.h>

/*LCD circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 7
 * LCD D5 pin to digital pin 6
 * LCD D6 pin to digital pin 5
 * LCD D7 pin to digital pin 4*/

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

// Message to display
String message = "";

// Data from outdoor module
String data = "";

// Which parameter should be shown
int parameter = 0;

void setup(){
    Serial.begin(38400);
    Serial1.begin(38400);

    // Set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
}

void loop(){
  // Update conditions informations
  while(Serial1.available() == 0)
  {
  }

  data = Serial1.readStringUntil(';');
  Serial.println(data);
  message = data;

  lcd.clear();

  lcd.setCursor(0, 0);

  switch(parameter)
  {
    case 0:
    lcd.print("Pressure:");
    lcd.setCursor(0, 1);
    message = message.substring(0, message.indexOf(',')) + " [hPa]";
    parameter++;
    break;
    
    case 1:
    lcd.print("Temperature:");
    lcd.setCursor(0, 1);
    message = message.substring(message.indexOf(',') + 1, message.lastIndexOf(',')) + " [" + (char)223 + "C]";
    parameter++;
    break;

    case 2:
    lcd.print("Humidity:");
    lcd.setCursor(0, 1);
    message = message.substring(message.lastIndexOf(',')  + 1) + " %";
    parameter = 0;
    break;
  }
  
  lcd.print(message);
}