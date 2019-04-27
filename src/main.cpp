#include <Arduino.h>
#include <Wire.h>

#include "DHT.h"
#define DHTPIN 2  
#define DHTTYPE DHT11  

// DallasTemperature configuration
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONEWIRE_PIN 7

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONEWIRE_PIN);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

DHT dht(DHTPIN, DHTTYPE);


//-------------------------------// 


void onRequest() {
}


void setup()
{
  Serial.begin(9600);
  sensors.begin();
  pinMode(0, INPUT);
    dht.begin();
}

void loop()
{


    // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

    // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);


  sensors.requestTemperatures();
  float waterTemp = sensors.getTempCByIndex(0);
  int lux = analogRead(0);
  int lux_mapped = map(lux, 0,1023, 0, 100);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  Serial.print("Water Temperature: ");
  Serial.print(waterTemp);
  Serial.print("C");
  
  Serial.print(" Lux: ");
  Serial.print(lux_mapped);
  Serial.print('%');
  Serial.println();


  delay(1000);

}


