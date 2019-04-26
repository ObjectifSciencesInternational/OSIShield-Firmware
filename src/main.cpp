#include <Arduino.h>
#include <Wire.h>

// DallasTemperature configuration
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONEWIRE_PIN 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONEWIRE_PIN);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);


//-------------------------------// 


void onRequest() {
  Serial.println("Request event");
  sensors.requestTemperatures();
  float waterTemp = sensors.getTempCByIndex(0);


}

void setup()
{
  Serial.begin(9600);
  sensors.begin();
  Wire.begin(8);
  // Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
  
}

void loop()
{
}

