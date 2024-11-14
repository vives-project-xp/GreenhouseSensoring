//Include libraries
#include <OneWire.h>
#include <DallasTemperature.h>
#include <GyverHTU21D.h>
#include <BH1750.h>

#include "sensor.h"
#include "connection.h"
#include "Wifi_config.h"

//Initialisatie namen van sensorwaarden voor home assistant
HaSensor bodemTempWaarde;
HaSensor omgevingTempWaarde;
HaSensor omgevingVochtWaarde;
HaSensor lichtWaarde;
HaSensor CO2Waarde;
HaSensor bodemVochtWaarde;
HaSensor NPKWaarde;
HaConnection connection;

// Datapin bodemtemperatuursensor
#define GPIO_BODEMTEMP 14
OneWire oneWire(GPIO_BODEMTEMP);
DallasTemperature bodemTemp(&oneWire);
float Celsius = 0;

//omgevingtemperatuursensor
GyverHTU21D htu;

//lichtsensor
BH1750 lightMeter;

void setup()
{
  bodemTemp.begin(); 
  lightMeter.begin();
  Serial.begin(9600);

  if (!htu.begin()) Serial.println(F("HTU21D error"));

  connection =  HaConnection(WIFI_SSID, WIFI_PASSWORD, 80, true);
  connection.setup();
  if (!connection.connected)
    return;

  bodemTempWaarde = HaSensor("soil_temperature", "°C");
  omgevingTempWaarde = HaSensor("ambient_temperature", "°C");
  omgevingVochtWaarde = HaSensor("humidity", "%");
  lichtWaarde = HaSensor("light", "lx");
  //waardes voor andere sensoren hier
}

void loop()
{ 
  // Send the command to get temperatures
  bodemTemp.requestTemperatures();  
  Celsius = bodemTemp.getTempCByIndex(0);
  bodemTempWaarde.setValue(Celsius);
  connection.sendData(bodemTempWaarde);
  Serial.print("Bodemtemperatuur: ");
  Serial.print(Celsius);
  Serial.print(" C    ");

  //omgevingstemp & omgevingsvocht
  float temp = htu.getTemperatureWait();
  float hum = htu.getHumidityWait();

  omgevingTempWaarde.setValue(temp);
  connection.sendData(omgevingTempWaarde);
  Serial.print("Omgevingstemperatuur: ");
  Serial.print(temp);
  Serial.println(" °C");

  omgevingVochtWaarde.setValue(hum);
  connection.sendData(omgevingVochtWaarde);
  Serial.print("Omgevingsvochtigheid: ");
  Serial.print(hum);
  Serial.println(" %");

  //lichtsensor
  float lux = lightMeter.readLightLevel();
  lichtWaarde.setValue(lux);
  connection.sendData(lichtWaarde);
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");

  //waardes andere sensoren verzenden hier

  delay(1000);
}