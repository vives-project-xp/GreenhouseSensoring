//Include libraries
#include <OneWire.h>
#include <DallasTemperature.h>

#include "sensor.h"
#include "connection.h"

HaSensor sensor;
HaConnection connection;

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 14
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

float Celsius = 0;
float Fahrenheit = 0;

void setup()
{
  sensors.begin(); //Begin serial communication
  Serial.begin(9600);
  connection =  HaConnection("devbit", "Dr@@dloos!", 80, true);
  connection.setup();
  if (!connection.connected)
    return;
  sensor = HaSensor("temperature", "°C");
}

void loop()
{ 
  // Send the command to get temperatures
  sensors.requestTemperatures();  

  Celsius = sensors.getTempCByIndex(0);
  Fahrenheit = sensors.toFahrenheit(0);

  sensor.setValue(Celsius);

  connection.sendData(sensor);

  Serial.print(Celsius);
  Serial.print(" C    ");
  delay(1000);
}