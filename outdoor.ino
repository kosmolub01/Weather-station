// Low power mode
#include "LowPower.h"

// To handle communication with BT module
#include <SoftwareSerial.h>

// BME
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// DHT
#include "DHT.h"   

// DHT signal pin
#define DHTPIN 3
// DHT type
#define DHTTYPE DHT22

// Location specific sea level pressure [hPa]
#define SEALEVELPRESSURE_HPA (1013.25)

// To handle communication with BT module
const byte rxPin = 5;
const byte txPin = 4;

// Set up a new SoftwareSerial object
SoftwareSerial mySerial (rxPin, txPin);

// Set up a new Adafruit_BME280 object
Adafruit_BME280 bme;

// Sensor definition
DHT dht(DHTPIN, DHTTYPE); 

String pressure;
float temperature, humidity;

// Single message to indoor module
String message;


void setup(){
    mySerial.begin(38400);
    Serial.begin(38400);

    pinMode(13, OUTPUT);    // sets the digital pin 13 as output

    if (!bme.begin(0x76)) {
        Serial.println("No BME280 found");
    }
    dht.begin();
}

void loop(){

  // Read pressure
  pressure = bme.readPressure() / 100.0F;

  // Read temperature and humidity
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
 
  // Make sure data is valid
  if (isnan(temperature) || isnan(humidity)){

    // If not, print message
    Serial.println("No data form DHT22");

  }

  digitalWrite(13, HIGH); // sets the digital pin 13 on
  delay(500);
  digitalWrite(13, LOW); // sets the digital pin 13

  message = pressure + "," + temperature + "," + humidity + ";";

  Serial.println("Message: " + message);
  mySerial.print(message);
  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  

}